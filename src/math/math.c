/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpiarova <zpiarova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 15:24:04 by zpiarova          #+#    #+#             */
/*   Updated: 2025/03/12 15:01:20 by zpiarova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

// make a function to get the 4x4 translation matrix
// t_coord translation_matrix[][]()
// {

// }

// TODO: MUST CHECK FOR CORRECTNESS AND IF THE MATRIX IS OK BUT I THINK IT LOOKS GOOD
// ALREADY MAPS ALL PIXELS DESCRIBED BY x AND y FROM SCREEN SPACE TO CAMERA SPACE TO 3D SPACE! <3
// maps coordinate from top-left 2d screen to the viewport plane in 3d
// in screen, one pixel is one unit defined by x and y, but they specify start of the pixel
// the middle of it is [x + 0.5, y + 0.5]
t_coord get_viewport_ray(t_camera c, t_viewport *v, int x, int y)
{
	// data needed to find transformation matrix
	t_coord P0; // this is variable for each ray
	t_coord Pnew;
	t_coord C0; // initial camera point for simplicity, C.new = camera.viewpoint
	t_coord v0; // initial camera vector for simplicity, vnew = camera.vector
	// vectors needed for teh 4x4 translation matrix
	t_coord forward;	// vector along y axis
	t_coord right;		// vector along x axis
	t_coord up;			// vector along z axis
	t_coord translation; // translation vector: Cnew - C0
	t_coord up_temp;	// temporary global vector (0, 0, 1) used for calculating
	// final vector 
	t_coord ray_vector; // resulting vector

	// initial simple position and direction of camera
	C0 = set_coord(0.0, 0.0, 0.0);
	v0 = set_coord(0.0, 1.0, 0.0);
	up_temp = set_coord(0.0, 0.0, 1.0);
	// applying the camera-to-world to transform P from camera space to world space
	// the matrix:
	// T = R(rotation) * Tr(translation) = [[ Rx Ry Rz Tx ]
	//										[ Fx Fy Fz Ty ]
	//										[ Ux Uy Uz Tz ]
	//										[  0  0  0  1 ]]
	forward = c.vector; // F = vnew = camera.vector --> normalized
	right = get_cross_product(up_temp, forward);
	normalize(&right);
	up = get_cross_product(right, forward);
	normalize(&up);
	translation.x = c.viewpoint.x - C0.x;
	translation.y = c.viewpoint.y - C0.y;
	translation.z = c.viewpoint.z - C0.z;
	if (x == 0 && y == 0)
	// P0 are world coordinates of point but when camera is in the default position: C[0, 0, 0], ->v(0, 0, 1)
	P0.x = scale(x + 0.5, - v->viewport_width / 2, v->viewport_width / 2, WIDTH);
	P0.y = v->d;
	P0.z = scale(y + 0.5, v->viewport_height / 2, - v->viewport_height / 2, HEIGHT);
	// so we have to apply the matrix to the point t get the transformed world coordinates
	Pnew.x = right.x * P0.x + right.y * P0.y + right.z * P0.z + translation.x;
	Pnew.y = forward.x * P0.x + forward.y * P0.y + forward.z * P0.z + translation.y;
	Pnew.z = up.x * P0.x + up.y * P0.y + up.z * P0.z + translation.z;
	ray_vector = make_vector(c.viewpoint, Pnew);
	if (x == 0 && y == 0)
		printf("P0 [%f, %f, %f]\nF (%f, %f, %f)\nR (%f, %f, %f)\nU (%f, %f, %f)\nT (%f, %f, %f)\nPnew [%f, %f, %f]\n -> final point vector v (%f, %f, %f)\n", P0.x, P0.y, P0.z, forward.x, forward.y, forward.z, right.x, right.y, right.z, up.x, up.y, up.z, translation.x, translation.y, translation.z, Pnew.x, Pnew.y, Pnew.z, ray_vector.x, ray_vector.y, ray_vector.z);
	return (ray_vector);
}

int shoot_rays(t_scene *scene)
{
	int     x;
	int     y;

	//t_coord viewport_point;
	//t_coord ray;
	// t_coord intersection;

	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
		{
			get_viewport_ray(scene->c, scene->viewport, x, y); // get coordinate on viewport as now we can make ray(vector) from camera through it to the scene
			//intersection = sphere_intersection(&viewport_point, &scene->c, scene->sp);
		}

	}
	return (0);
}
