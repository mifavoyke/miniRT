/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpiarova <zpiarova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 15:24:04 by zpiarova          #+#    #+#             */
/*   Updated: 2025/03/11 21:30:22 by zpiarova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

// TODO: MUST CHECK FOR CORRECTNESS AND IF THE MATRIX IS OK BUT I THINK IT LOOKS GOOD
// ALREADY MAPS ALL PIXELS DESCRIBED BY x AND y FROM SCREEN SPACE TO CAMERA SPACE TO 3D SPACE! <3
// maps coordinate from top-left 2d screen to the viewport plane in 3d
// in screen, one pixel is one unit defined by x and y, but they specify start of the pixel
// the middle of it is [x + 0.5, y + 0.5]
t_coord get_viewport_ray(t_camera c, t_viewport *v, int x, int y)
{
	t_coord P0;
	t_coord Pnew;
	t_coord C0; // initial camera point for simplicity
	t_coord v0; // initial camera vector for simplicity
	t_coord right;		// vector along x axis
	t_coord forward;	// vector along y axis
	t_coord up;			// vector along z axis 
	t_coord translation; // translation vector: Cnew - C0
	t_coord up_temp;	// temporary global vector (0, 0, 1) used for calculating
	t_coord ray_vector; // resulting vector 
	
	// initial simple position and direction of camera
	C0.x = 0.0;
	C0.y = 0.0;
	C0.z = 0.0;
	v0.x = 0.0;
	v0.y = 1.0;
	v0.z = 0.0;
	up_temp.x = 0.0;
	up_temp.y = 0.0;
	up_temp.z = 1.0;
	// P are coordinates of point in viewport in 3d but for now only when camera is in the default position: C[0, 0, 0], ->v(0, 0, 1)
	P0.x = scale(x + 0.5, - v->viewport_width / 2, v->viewport_width / 2, WIDTH);
	P0.y = 1;
	P0.z = scale(y + 0.5, v->viewport_height / 2, - v->viewport_height / 2, HEIGHT);
	forward = c.vector;
	right = get_cross_product(up_temp, forward);
	up = get_cross_product(forward, right);
	translation.x = c.viewpoint.x - C0.x;
	translation.y = c.viewpoint.y - C0.y;
	translation.z = c.viewpoint.z - C0.z;
	// applying the camera-to-world to transform P from camera space to world space
	// the matrix:	
	// T = R(rotation) * Tr(translation) = [[ Rx Ry Rz Tx ]
	//										[ Fx Fy Fz Ty ]
	//										[ Ux Uy Uz Tz ]
	//										[  0  0  0  1 ]]
	Pnew.x = right.x * P0.x + right.y * P0.y + right.z * P0.z + translation.x;
	Pnew.y = forward.x * P0.x + forward.y * P0.y + forward.z * P0.z + translation.y;
	Pnew.z = up.x * P0.x + up.y * P0.y + up.z * P0.z + translation.z;
	ray_vector = make_vector(c.viewpoint, Pnew);
	if (x == 0 && y == 0)
		printf("P0[%f, %f, %f]\nR(%f, %f, %f)\nU(%f, %f, %f)\nPnew[%f, %f, %f]\n -> final point vector v(%f, %f, %f)\n", P0.x, P0.y, P0.z, right.x, right.y, right.z, up.x, up.y, up.z, Pnew.x, Pnew.y, Pnew.z, ray_vector.x, ray_vector.y, ray_vector.z);
	return (ray_vector);
}

/*
// calculates the intersection of a sphere with the ray
// @param V is the pixel
t_coord sphere_intersection(t_coord *V, t_camera *C, t_sphere *sp)
{
	t_coord r;
	t_coord q;
	
	float a;
	float b;
	float c;
	
	float t1;
	float t2;
	float discriminant;
	
	r = make_vector(C->viewpoint, *V); // r = V - C --> vector in the direction from the camera to the viewpoint coordinate corresponding to a pixel in the screen 
	q = make_vector(C->viewpoint, sp->centre);  // q = C - S --> vector in the direction of the camera and the sphere centre

	a = dot_product(r, r);
	b = 2 * (dot_product(q, r));
	c = dot_product(q, q) - sp->diameter / 2;
	
	// this maybe has to be changed, what if the one where  we use + sqrt(D) is not root but the - sqrt(D) is the root
	discriminant = get_discriminant(a, b, c);
	if (discriminant >= 0)
		t1 = (-b + sqrt(discriminant)) / (2 * a);
	if (discriminant > 0)
		t2 = (-b - sqrt(discriminant)) / (2 * a);

		
		// dosad the t variable value that we now know to the equation P = C + t*(V - C);
	return (*V); // TODO: for now we return V, but not correct, just to shut up the errors 
}
*/

int shoot_rays(t_scene *scene)
{
	int     x;
	int     y;

	t_coord viewport_point;
	//t_coord ray;
	// t_coord intersection;

	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
		{
			viewport_point = get_viewport_ray(scene->c, scene->viewport, x, y); // get coordinate on viewport as now we can make ray(vector) from camera through it to the scene
			//intersection = sphere_intersection(&viewport_point, &scene->c, scene->sp);
		}
		
	}
	return (0);
}
