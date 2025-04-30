/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpiarova <zpiarova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 15:24:04 by zpiarova          #+#    #+#             */
/*   Updated: 2025/04/30 17:14:38 by zpiarova         ###   ########.fr       */
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
	t_matrix	tm;
	t_coord		global_up;

	tm.Tr = set_coord(c.point.x, c.point.y, c.point.z);
	global_up = set_coord(0.0, 0.0, 1.0);
	tm.F = c.vector;
	if (tm.F.x == 0 && tm.F.y == 0 && tm.F.z == 1)
	{
		tm.U = set_coord(0, -1, 0);
		tm.R = set_coord(1, 0, 0);
	}
	else if (tm.F.x == 0 && tm.F.y == 0 && tm.F.z == -1)
	{
		tm.U = set_coord(0, 1, 0);
		tm.R = set_coord(1, 0, 0);
	}
	else
	{
		tm.R = get_cross_product(tm.F, global_up);
		normalize(&tm.R);
		tm.U = get_cross_product(tm.R, tm.F);
		normalize(&tm.U);
	}
	return (tm);
}

// maps coordinate from top-left 2d screen to the viewport plane in 3D
// and applies Tm to find final vector from camera to that pixel in 3D=>THE RAY
t_coord	get_viewport_ray(t_scene *scene, t_matrix Tm, int x, int y)
{
	t_coord	pv;
	t_coord	p_new;
	t_coord	ray_vector;

	pv.x = scale(x + 0.5, -scene->viewport_width / 2,
			scene->viewport_width / 2, WIDTH);
	pv.y = scene->viewport_distance;
	pv.z = scale(y + 0.5, scene->viewport_height / 2,
			-scene->viewport_height / 2, HEIGHT);
	p_new.x = Tm.R.x * pv.x + Tm.F.x * pv.y + Tm.U.x * pv.z + Tm.Tr.x;
	p_new.y = Tm.R.y * pv.x + Tm.F.y * pv.y + Tm.U.y * pv.z + Tm.Tr.y;
	p_new.z = Tm.R.z * pv.x + Tm.F.z * pv.y + Tm.U.z * pv.z + Tm.Tr.z;
	ray_vector = make_vector(scene->c.point, p_new);
	normalize(&ray_vector);
	return (ray_vector);
}

// creates linked list of intersections of ray with all scene objects
// --> for one pixel, checks all objects in the scene
t_inter	*create_intersection_list(t_scene *scene, t_coord ray)
{
	t_sphere	*temp_sp;
	t_plane		*temp_pl;
	t_cylinder	*temp_cy;
	t_inter		*head;
	t_inter		*new_node;

	head = NULL;
	new_node = NULL;
	temp_sp = scene->sp;
	temp_cy = scene->cy;
	temp_pl = scene->pl;
	while (temp_sp)
	{
		new_node = find_sphere_intersections(ray, scene->c, (void *)temp_sp);
		append_node(new_node, &head);
		temp_sp = temp_sp->next;
	}
	while (temp_cy)
	{
		new_node = find_cylinder_intersections(ray, scene->c, (void *)temp_cy);
		append_node(new_node, &head);
		temp_cy = temp_cy->next;
	}
	while (temp_pl)
	{
		new_node = find_plane_intersections(ray, scene->c, (void *)temp_pl);
		append_node(new_node, &head);
		temp_pl = temp_pl->next;
	}
	merge_sort(&head);
	return (head);
}

// iterates over all pixels of the screen 
// finds ray from camera through each pixel center
// for each ray, creates list of intersections with all objects and sorts them
// so the closest intersection in front of the camera is head of the list
// one by one frees and repopulates minirt->intersections array of linked lists
// also fills pixels array with colour correspodning to object for each pixel
int	shoot_rays(t_minirt *minirt, t_scene *scene)
{
	int		x;
	int		y;
	t_coord	ray;
	t_inter	*intersection_list;

	y = -1;
	while (++y < minirt->img_height)
	{
		x = -1;
		while (++x < minirt->img_width)
		{
			ray = get_viewport_ray(scene, scene->Tm, x, y);
			intersection_list = create_intersection_list(scene, ray);
			if (minirt->intersection[y][x])
				free_list(&minirt->intersection[y][x], free);
			minirt->intersection[y][x] = intersection_list;
			if (intersection_list)
				minirt->pixels[y][x] = intersection_list->colour;
			else
				minirt->pixels[y][x] = minirt->scene->bg;
		}
	}
	return (0);
}
