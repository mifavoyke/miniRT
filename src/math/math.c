/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpiarova <zpiarova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 15:24:04 by zpiarova          #+#    #+#             */
/*   Updated: 2025/03/10 21:07:31 by zpiarova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

// mapping screen pixel coordinate to a coordinate in the scene, mapped to the viewport size
// x and y are coordinates on the screen
// TODO: not workng properly, check some vector math t understand better 
void get_viewport_corners(t_viewport *v, t_camera c)
{
	t_coord temp_vector;
	t_coord normal;

	// we have lengths, angles, coordinates of S(viewport_centre) and C(camera.viewpoint), and CS vector(camera.vector), and it is right-angled at S
	// find perpendicular vector
		// Choose any arbitrary vector t that is not parallel to →CS - simple choice is (1, 0, 0), (0,1,0), (0,0,1)
		temp_vector.x = 1;
		temp_vector.y = 0;
		temp_vector.z = 0;
		// but if it happend to be collinear with CS, pick another one of them 
		if (are_collinear(c.vector, temp_vector))
		{
			temp_vector.x = 0;
			temp_vector.y = 1;
			temp_vector.z = 0;
		}
		// compute the cross product: 𝑁 = →CS × t --> this gives perpendicular vector N
		normal = get_cross_product(c.vector, temp_vector);
		// normalize N to get a unit vector: N(normalized) = N / |N|
		normalize(&normal);
	// compute third point C(Vtl, Vtr, Vbl, Vbr) --> 𝐶 = S + |SV|(corner_distance) * N(normalized) --> expand for coordinates x, y, z
	v->Vtr.x = v->viewport_centre.x + v->corner_distance * normal.x;
	v->Vtr.y = v->viewport_centre.y + v->corner_distance * normal.y;
	v->Vtr.z = v->viewport_centre.z + v->corner_distance * normal.z;
	//printf("|Vtr| = %f, Vtr [%f, %f, %f]\n", v->corner_distance, v->Vtr.x, v->Vtr.y, v->Vtr.z);
	
	// Vtl = ;
	// Vbl = ;
	// Vbr = ;
}

// TODO: maps coordinate from screen to the 3D coordinates, using the scale function and corner points 
t_coord get_viewport_coordinate(t_viewport *v, int x, int y)
{
	t_coord V;
	
	(void)v;
	V.x = x;
	V.y = y;
	V.z = 0;
	//printf("screen: P[%f, %f]\n", V.x, V.y);
	return (V);
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
			viewport_point = get_viewport_coordinate(scene->viewport, x, y); // get coordinate on viewport as now we can make ray(vector) from camera through it to the scene
			//intersection = sphere_intersection(&viewport_point, &scene->c, scene->sp);
		}
		
	}
	return (0);
}
