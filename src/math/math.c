/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpiarova <zpiarova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 15:24:04 by zpiarova          #+#    #+#             */
/*   Updated: 2025/03/11 17:31:53 by zpiarova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

// TODO: maps coordinate from screen to the 3D coordinates, using the scale function and corner points 
// maps coordinate from top-left 2d screen to the viewport plane in 3d
// in screen, one pixel is one unit defined by x and y, but they specify start of the pixel
// the middle of it is [x + 0.5, y + 0.5]
t_coord get_viewport_ray(t_camera c, t_viewport *v, int x, int y)
{
	t_coord P;
	t_coord ray_vector;
	
	// P are camera space coordinates 
	P.x = scale(x + 0.5, - v->viewport_width / 2, v->viewport_width / 2, WIDTH);
	P.y = scale(y + 0.5, v->viewport_height / 2, - v->viewport_height / 2, HEIGHT);
	P.z = 1;
	ray_vector = make_vector(c.viewpoint, P); // ! this does not calculate for translation and rotation
	// 4. Apply the final camera-to-world transformation 4x4 matrix transforms the coordinates in screen space to world space.
	
	// 1. transform from 0,0 in top left to 0 in center
	// 2. scale the coordinates from 600x400 to Vw and Vh								_
	// 3. do not shoot ray through top-left corner of each pixel, but find its center |X|
	if (x == 599 && y == 399)
		printf("viewport: P[%f, %f, %f] | ->v (%f, %f, %f)\n", P.x, P.y, P.z, ray_vector.x, ray_vector.y, ray_vector.z);
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
