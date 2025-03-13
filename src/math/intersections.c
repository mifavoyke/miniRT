/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpiarova <zpiarova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 10:47:46 by zpiarova          #+#    #+#             */
/*   Updated: 2025/03/13 17:10:17 by zpiarova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

int sphere_intersection(t_coord ray, t_camera cam, t_sphere *sp)
{
	t_coord camera_to_sphere_center;
	float a;
	float b;
	float c;
	float discriminant;
	int roots;

	//printf("S[%f, %f, %f] O[%f, %f, %f] ->SO: (%f, %f, %f)\n", sp.centre.x, sp.centre.y, sp.centre.z, cam.viewpoint.x, cam.viewpoint.y, cam.viewpoint.z, camera_to_sphere_center.x, camera_to_sphere_center.y, camera_to_sphere_center.z);
	camera_to_sphere_center = make_vector(sp->centre, cam.viewpoint);
	
	a = get_dot_product(ray, ray); // looks ok
	b = 2 * get_dot_product(camera_to_sphere_center, ray);
	c = get_dot_product(camera_to_sphere_center, camera_to_sphere_center) - pow((sp->diameter) / 2, 2);
	discriminant = pow(b, 2) - (4 * a * c);
	if (discriminant < 0)
		roots = 0;
	else if (discriminant == 0)
		roots = 1;
	else
		roots = 2;
	printf("a: %f, b: %f, c: %f, D = %f, roots: %d\n", a, b, c, discriminant, roots);
	
	return (discriminant); // TODO: for now we return V, but not correct, just to shut up the errors
}
