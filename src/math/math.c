/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpiarova <zpiarova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 15:24:04 by zpiarova          #+#    #+#             */
/*   Updated: 2025/04/15 11:43:25 by zpiarova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

// finds transformation matrix of camera from origin to defined position C
// from C0[0,0,0] and v0(0, 1, 0) to Cn(cx, cy, cz) and vn(vx, vy, vz)
// to be applied to all points of the viewport - each pixel centre
// maps camera axis to world axis
// initially, camera is placed in origin and its forward orientation is along y
// then:
// 1. new orientation vn is set as camera's y(forward) axis
// 2. camera's x(right) axis is found as cross product of camera forward and global up vectors
// 3. camera's z(camera's up) axis is found as cross product of camera's forward and camera's right directions
// --> the R, F, U vectors form the matrice's x, y, z columns
// 4. translation from point C0 to point Cn is applied as last column
// final matrix: Tm = [ Rx  Fx  Ux  Tx ]   [ P0x ]
//					  [ Ry  Fy  Uy  Ty ] * [ P0y ]
//					  [ Rz  Fz  Uz  Ty ] * [ P0z ]
//					  [  0   0   0   1 ] * [  1  ]
t_matrix find_transformation_matrix(t_camera c)
{
	t_matrix Tm;
	t_coord global_up; // global up to be able to create cross product

	global_up = set_coord(0.0, 0.0, 1.0);
	Tm.Tr = set_coord(c.point.x, c.point.y, c.point.z);
	Tm.F = c.vector;
	if (Tm.F.x == 0 && Tm.F.y == 0 && Tm.F.z == 1) // if F (0, 0, 1) - we would be making cross product of colinear vectors which is wrong
	{
		Tm.U = set_coord(0, -1, 0);
		Tm.R = set_coord(1, 0, 0);
	}
	else if (Tm.F.x == 0 && Tm.F.y == 0 && Tm.F.z == -1) // if F (0, 0, -1)
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

// maps coordinate from top-left 2d screen to the viewport plane in 3d
// and finds the final vector from camera to that pixel in 3D => the ray
// in screen, one pixel is one unit defined by x and y, but they specify start of the pixel
// the middle of pixel is pixel x, y pls 0.5 --> P[x + 0.5, y + 0.5]
t_coord get_viewport_ray(t_scene *scene, t_matrix Tm, int x, int y)
{
	t_coord Pv;			// point in viewport without transformation
	t_coord Pnew;		// point in 3d space relative to camera
	t_coord ray_vector; // resulting vector

	// transform coordinate of center of the pixel from 2D screen coord relative to top left corner of the screen to 2D viewport coord relative to center of viewport
	Pv.x = scale(x + 0.5, -scene->viewport->viewport_width / 2, scene->viewport->viewport_width / 2, WIDTH);
	Pv.y = scene->viewport->d;
	Pv.z = scale(y + 0.5, scene->viewport->viewport_height / 2, -scene->viewport->viewport_height / 2, HEIGHT);
	// applying transformation matrix to point P0 to get its position in 3D
	Pnew.x = Tm.R.x * Pv.x + Tm.F.x * Pv.y + Tm.U.x * Pv.z + Tm.Tr.x;
	Pnew.y = Tm.R.y * Pv.x + Tm.F.y * Pv.y + Tm.U.y * Pv.z + Tm.Tr.y;
	Pnew.z = Tm.R.z * Pv.x + Tm.F.z * Pv.y + Tm.U.z * Pv.z + Tm.Tr.z;
	ray_vector = make_vector(scene->c.point, Pnew);
	return (ray_vector);
}

// creates linked list of all intersections of a ray with all scene objects (for one pixel, checks all objects)
// is not sorted, the intersections are in order same as they are ordered in the .rt file - must be sorted
// HAS TO BE FREED 
t_inter *create_intersection_list(t_scene *scene, t_coord ray)
{
	t_sphere *temp_sp; // maybe create a void * list of objects - spheres,planes, cylinders
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
		new_node = find_sphere_intersections(ray, scene->c, temp_sp, scene->l.lightpoint);
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
		new_node = find_plane_intersections(ray, scene->c, temp_pl, scene->l.lightpoint);
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
int shoot_rays(t_minirt *minirt, t_scene *scene)
{
	int x;
	int y;
	t_matrix Tm;
	t_coord ray;
	t_inter *intersection_list;

	minirt->intersection = allocate_inter(minirt->img_width, minirt->img_height);
	if (!minirt->intersection)
		return (ERROR);
	Tm = find_transformation_matrix(scene->c);
	y = -1;
	while (++y < minirt->img_height)
	{
		x = -1;
		while (++x < minirt->img_width)
		{
			ray = get_viewport_ray(scene, Tm, x, y); // get coordinate on viewport as now we can make ray(vector) from camera through it to the scene
			intersection_list = create_intersection_list(scene, ray);
			merge_sort(intersection_list); // order intersection list
			minirt->intersection[y][x] = intersection_list; // populate the intersection list
			/*###### following if-else is temporary ###########################*/
			if (intersection_list)
				minirt->pixels[y][x] = intersection_list->colour;
			else
				minirt->pixels[y][x] = minirt->scene->background;
			/*##################################################################*/
			// DECIDE: APPLY LIGHT HERE OR ITERATE OVER THE SCREEN ONE MORE TIME ? AS YOU DO IN LIGHT.C IN THE LAST FUNCTION -Z.
		}
	}
	return (0);
}
