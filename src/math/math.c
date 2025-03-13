/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpiarova <zpiarova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 15:24:04 by zpiarova          #+#    #+#             */
/*   Updated: 2025/03/13 14:07:08 by zpiarova         ###   ########.fr       */
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
	Tm.Tr = set_coord(c.viewpoint.x, c.viewpoint.y, c.viewpoint.z);
	Tm.F = c.vector;
	if (Tm.F.x == 0 && Tm.F.y == 0 && Tm.F.z == 1) // if F (0, 0, 1) - we would be making cross product of colinera vectors which is wrong
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
	return(Tm);
}

// maps coordinate from top-left 2d screen to the viewport plane in 3d
// and finds the final vector from camera to that pixel in 3D => the ray
// in screen, one pixel is one unit defined by x and y, but they specify start of the pixel
// the middle of pixel is pixel x, y pls 0.5 --> P[x + 0.5, y + 0.5]
t_coord get_viewport_ray(t_scene *scene, t_matrix Tm, int x, int y)
{
	t_coord Pv; // point in viewport without transformation
	t_coord Pnew; // point in 3d space relative to camera
	t_coord ray_vector; // resulting vector
	
	Pv.x = scale(x + 0.5, - scene->viewport->viewport_width / 2, scene->viewport->viewport_width / 2, WIDTH);
	Pv.y = scene->viewport->d;
	Pv.z = scale(y + 0.5, scene->viewport->viewport_height / 2, - scene->viewport->viewport_height / 2, HEIGHT);
	// applying transformation matrix to point P0 to get its position in 3D 
	Pnew.x = Tm.R.x * Pv.x + Tm.F.x * Pv.y + Tm.U.x * Pv.z + Tm.Tr.x;
	Pnew.y = Tm.R.y * Pv.x + Tm.F.y * Pv.y + Tm.U.y * Pv.z + Tm.Tr.y;
	Pnew.z = Tm.R.z * Pv.x + Tm.F.z * Pv.y + Tm.U.z * Pv.z + Tm.Tr.z;
	ray_vector = make_vector(scene->c.viewpoint, Pnew);
	if (x == 0 && y == 0)
	{
	// 	printf("Pv [%f, %f, %f]\n", Pv.x, Pv.y, Pv.z);
	// 	printf("F (%f, %f, %f)   R (%f, %f, %f)   U (%f, %f, %f)\n", Fn.x, Fn.y, Fn.z, R.x, R.y, R.z, U.x, U.y, U.z);
		printf("Pnew [%f, %f, %f]\n", Pnew.x, Pnew.y, Pnew.z);
	// 	printf("ray vector [%f, %f, %f] normalized: %d\n", ray_vector.x, ray_vector.y, ray_vector.z, is_vector_normalized(ray_vector));
	}
	return (ray_vector);
}

int shoot_rays(t_scene *scene)
{
	int			x;
	int			y;
	t_matrix	Tm;
	t_coord		ray;

	Tm = find_transformation_matrix(scene->c);
	//t_coord viewport_point;
	// t_coord intersection;

	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
		{
			
			ray = get_viewport_ray(scene, Tm, x, y); // get coordinate on viewport as now we can make ray(vector) from camera through it to the scene
			if (x == 0 && y == 0)
				printf("ray vector: r(%f, %f, %f) normalized: %d\n", ray.x, ray.y, ray.z, is_vector_normalized(ray));
			//intersection = sphere_intersection(&viewport_point, &scene->c, scene->sp);
		}

	}
	return (0);
}