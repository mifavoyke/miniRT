/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpiarova <zpiarova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 10:47:46 by zpiarova          #+#    #+#             */
/*   Updated: 2025/03/20 16:26:45 by zpiarova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

// based on parametric equations for sphere and ray
// any point in ray: P = C + t*ray
// any point in sphere: |P−C|=r --> sqrt(P-C o P - C) = r --> (P-c)o(P-C) = r^2
t_inter *sphere_intersections(t_coord ray, t_camera cam, t_sphere *sp)
{
	t_coord camera_to_sphere_center;
	float a;
	float b;
	float c;
	float discriminant;
	float t1;
	float t2;
	t_inter *inter1;
	t_inter *inter2;

	// underlying math
	camera_to_sphere_center = make_vector(sp->centre, cam.viewpoint);
	a = get_dot_product(ray, ray);
	b = 2 * get_dot_product(camera_to_sphere_center, ray);
	c = get_dot_product(camera_to_sphere_center, camera_to_sphere_center) - pow((sp->diameter) / 2, 2);
	discriminant = pow(b, 2) - (4 * a * c);
	
	// finding if it intersects
	if (discriminant < 0)  // no solution
		return (NULL);
	else if (discriminant == 0) //  1 solution - t1 == t2 - touching the surface 
	{
		t1 = (-b + sqrt(discriminant)) / 2*a;
		t2 = t1;
	}
	else // 2 solutions - in t1 enters and in t2 leaves
	{
		t1 = (-b + sqrt(discriminant)) / 2*a;
		t2 = (-b - sqrt(discriminant)) / 2*a;
	}
	
	// finding intersection points
	if (t1 < 1) // logical condition, can change 1 to 0, that means it is behind the camera
		inter1 = NULL;
	else
	{
		inter1 = (t_inter *)malloc(sizeof(t_inter));
		inter1->obj = (void *)sp;
		inter1->type = SPHERE;
		inter1->distance = t1;
		inter1->inter_point.x = cam.viewpoint.x + t1 * ray.x;
		inter1->inter_point.y = cam.viewpoint.y + t1 * ray.y;
		inter1->inter_point.z = cam.viewpoint.z + t1 * ray.z;
		inter1->next = NULL;
	}

	if (t2 < 1 || t2 == t1)
		inter2 = NULL;
	else
	{
		inter2 = (t_inter *)malloc(sizeof(t_inter));
		inter2->obj = (void *)sp;
		inter2->type = SPHERE;
		inter2->distance = t2;
		inter2->inter_point.x = cam.viewpoint.x + t2 * ray.x;
		inter2->inter_point.y = cam.viewpoint.y + t2 * ray.y;
		inter2->inter_point.z = cam.viewpoint.z + t2 * ray.z;
		inter2->next = NULL;
	}

	// return intersections that are in front of the camera
	if (inter1 && inter2)
		inter1->next = inter2;
	if (inter1)
		return (inter1);
	if (inter2)
		return (inter2);
	return (NULL);
}

t_inter *cylinder_intersections(t_coord ray, t_camera cam, t_cylinder *cy)
{
	(void)ray;
	(void)cam;
	(void)cy;
	return (NULL);
}

t_inter *plane_intersections(t_coord ray, t_camera cam, t_plane *pl)
{
	(void)ray;
	(void)cam;
	(void)pl;
	return (NULL);
}
