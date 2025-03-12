/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpiarova <zpiarova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 10:47:46 by zpiarova          #+#    #+#             */
/*   Updated: 2025/03/12 10:48:27 by zpiarova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

// calculates the intersection of a sphere with the ray
// @param V is the pixel
/*
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
