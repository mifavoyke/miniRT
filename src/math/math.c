/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpiarova <zpiarova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 15:24:04 by zpiarova          #+#    #+#             */
/*   Updated: 2025/04/30 11:55:57 by zpiarova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

// maps camera axis to world axis
// cam orientation is described by vectors R,F,U defined in world coordinates
// this matrix assumes that init camera local vectors in world coortinates are:
// 		 Right = [1, 0, 0] - along x
// 	   Forward = [0, 1, 0] - along y
//			Up = [0, 0, 1] - along z
//    Position = [0, 0, 0] - placed in Origin
// So the initial matrix Tm0 is:
//				 | 1  0  0  0 |
//				 | 0  1  0  0 |
//				 | 0  0  1  0 |
//				 | 0  0  0  1 |
//  final : Tm = [ Rx  Fx  Ux  Tx ]   [ P0x ]
//	matrix		 [ Ry  Fy  Uy  Ty ] * [ P0y ]
//				 [ Rz  Fz  Uz  Tz ] * [ P0z ]
//				 [  0   0   0   1 ] * [  1  ]
// if F(0, 0, 1/-1) we would be making cross product of colinear vectors !wrong
// global up to be able to create cross product
t_matrix	find_transformation_matrix(t_camera c)
{
	t_matrix	Tm;
	t_coord		global_up;

	Tm.Tr = set_coord(c.point.x, c.point.y, c.point.z);
	global_up = set_coord(0.0, 0.0, 1.0);
	Tm.F = c.vector;
	if (Tm.F.x == 0 && Tm.F.y == 0 && Tm.F.z == 1)
	{
		Tm.U = set_coord(0, -1, 0);
		Tm.R = set_coord(1, 0, 0);
	}
	else if (Tm.F.x == 0 && Tm.F.y == 0 && Tm.F.z == -1)
	{
		Tm.U = set_coord(0, 1, 0);
		Tm.R = set_coord(1, 0, 0);
	}
	else
	{
		Tm.R = get_cross_product(Tm.F, global_up);
		normalize(&Tm.R);
		Tm.U = get_cross_product(Tm.R, Tm.F);
		normalize(&Tm.U);
	}
	return (Tm);
}

// maps coordinate from top-left 2d screen to the viewport plane in 3D
// and applies Tm to find final vector from camera to that pixel in 3D=>THE RAY
t_coord	get_viewport_ray(t_scene *scene, t_matrix Tm, int x, int y)
{
	t_coord	Pv;
	t_coord	Pnew;
	t_coord	ray_vector;

	Pv.x = scale(x + 0.5, -scene->viewport_width / 2,
		scene->viewport_width / 2, WIDTH);
	Pv.y = scene->viewport_distance;
	Pv.z = scale(y + 0.5, scene->viewport_height / 2,
		-scene->viewport_height / 2, HEIGHT);
	Pnew.x = Tm.R.x * Pv.x + Tm.F.x * Pv.y + Tm.U.x * Pv.z + Tm.Tr.x;
	Pnew.y = Tm.R.y * Pv.x + Tm.F.y * Pv.y + Tm.U.y * Pv.z + Tm.Tr.y;
	Pnew.z = Tm.R.z * Pv.x + Tm.F.z * Pv.y + Tm.U.z * Pv.z + Tm.Tr.z;
	ray_vector = make_vector(scene->c.point, Pnew);
	normalize(&ray_vector);
	return (ray_vector);
}

// void find_oject_intersections(enum e_obj_t type, void *obj, void *func())
// {
	
// }

// creates linked list of intersections of ray with all scene objects
// --> for one pixel, checks all objects
t_inter *create_intersection_list(t_scene *scene, t_coord ray)
{
	t_sphere *temp_sp;
	t_plane *temp_pl;
	t_cylinder *temp_cy;
	t_inter *head;
	t_inter *new_node;

	head = NULL;
	new_node = NULL;
	temp_sp = scene->sp;
	temp_cy = scene->cy;
	temp_pl = scene->pl;
	while (temp_sp)
	{
		new_node = find_sphere_intersections(ray, scene->c, temp_sp);
		if (new_node != NULL)
		{
			new_node->colour = temp_sp->colour;
			append_node(new_node, &head);
		}
		temp_sp = temp_sp->next;
	}
	while (temp_cy)
	{
		new_node = find_cylinder_intersections(ray, scene->c, temp_cy);
		if (new_node != NULL)
		{
			new_node->colour = temp_cy->colour;
			append_node(new_node, &head);
		}
		temp_cy = temp_cy->next;
	}
	while (temp_pl)
	{
		new_node = find_plane_intersections(ray, scene->c, temp_pl);
		if (new_node != NULL)
		{
			new_node->colour = temp_pl->colour;
			append_node(new_node, &head);
		}
		temp_pl = temp_pl->next;
	}
	return (head);
}

// iterates over all pixels of the screen 
// finds ray from camera through each pixel center
// for each ray, creates list of intersections with all objects and sorts them so the closest intersection is head of the list
// result is the populated minirt->intersections 2d array of linked lists
int shoot_rays(t_minirt *minirt, t_scene *scene) // i moved the allocate intersection function one level up to the generate_image(), seemed more logical
{
	int x;
	int y;
	t_coord ray;
	t_inter *intersection_list;

	y = -1;
	while (++y < minirt->img_height)
	{
		x = -1;
		while (++x < minirt->img_width)
		{
			ray = get_viewport_ray(scene, scene->Tm, x, y); // get coordinate on viewport as now we can make ray(vector) from camera through it to the scene
			intersection_list = create_intersection_list(scene, ray);
			merge_sort(&intersection_list); // order intersection list
			// print_list(intersection_list, x, y);
			if (minirt->intersection[y][x]) // ERROR happens because when we resize, the new size is checked for x,y, but befre nothing as there so we try to access memory that was not used
				free_list(&minirt->intersection[y][x], free); // ERROR
			minirt->intersection[y][x] = intersection_list; // populate the intersection list
			/*###### following if-else is temporary - but cannot take it out becasue it wont work ??  ###########################*/
			if (intersection_list)
				minirt->pixels[y][x] = intersection_list->colour;
			else
				minirt->pixels[y][x] = minirt->scene->bg;
		}
	}
	return (0);
}


