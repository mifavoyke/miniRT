/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhusieva <yhusieva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 10:47:46 by zpiarova          #+#    #+#             */
/*   Updated: 2025/03/15 13:49:20 by yhusieva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

// based on parametric equations for sphere and ray
// P = C + t*ray
// |
int sphere_intersection(t_coord ray, t_camera cam, t_sphere *sp) // i need a lil more explanation on that - yeva
{
	t_coord camera_to_sphere_center;
	float a;
	float b;
	float c;
	float discriminant;
	int roots;

	camera_to_sphere_center = make_vector(sp->centre, cam.viewpoint);
	
	a = get_dot_product(ray, ray);
	b = 2 * get_dot_product(camera_to_sphere_center, ray);
	c = get_dot_product(camera_to_sphere_center, camera_to_sphere_center) - pow((sp->diameter) / 2, 2);
	discriminant = pow(b, 2) - (4 * a * c);
	if (discriminant < 0)
		roots = 0;
	else if (discriminant == 0)
		roots = 1;
	else
		roots = 2;
	// printf("a: %f, b: %f, c: %f, D = %f, roots: %d\n", a, b, c, discriminant, roots);
	return (discriminant); // TODO: for now we return V, but not correct, just to shut up the errors
}
