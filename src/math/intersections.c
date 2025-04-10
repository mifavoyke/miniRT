/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhusieva <yhusieva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 10:47:46 by zpiarova          #+#    #+#             */
/*   Updated: 2025/04/03 16:58:05 by yhusieva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

// based on parametric equations for sphere and ray
// any point in ray: P = C + t*ray
// any point in sphere: |P−C|=r --> sqrt(P-C o P - C) = r --> (P-c)o(P-C) = r^2
t_inter *sphere_intersections(t_coord ray, t_camera cam, t_sphere *sp, t_coord lightpoint)
{
	t_coord camera_to_sphere_center;
	t_coord inter_to_light;
	float a;
	float b;
	float c;
	float discriminant;
	float t1;
	float t2;
	t_inter *inter1;
	t_inter *inter2;

	// underlying math
	camera_to_sphere_center = make_vector(sp->centre, cam.point);
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
		inter1->point = set_coord(cam.point.x + t1 * ray.x, cam.point.y + t1 * ray.y, cam.point.z + t1 * ray.z);
		inter_to_light = make_vector(inter1->point, lightpoint);
		inter1->dist_to_light = get_dot_product(inter_to_light, inter_to_light);
		// printf("distance to light %f\n", inter1->dist_to_light);
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
		inter2->point = set_coord(cam.point.x + t2 * ray.x, cam.point.y + t2 * ray.y, cam.point.z + t2 * ray.z);
		inter_to_light = make_vector(inter2->point, lightpoint);
		inter2->dist_to_light = get_dot_product(inter_to_light, inter_to_light);
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

// any point in plane: (P - Q ) * n = 0 --> Q = given point in plane, P = intersection point, n = surface normal
// any point in ray: P = C + t*ray 
// t = ((Q - C) * n) / (ray * n)
// t = ((point in plane - point on line=camera) * normal) / (ray * normal)
t_inter *plane_intersections(t_coord ray, t_camera cam, t_plane *pl, t_coord lightpoint)
{
	float t;
	t_inter *inter;
	t_coord temp_vector; // Q - C 
	t_coord inter_to_light;

	temp_vector = make_vector(pl->point, cam.point);
	t = get_dot_product(temp_vector, pl->vector) / get_dot_product(ray, pl->vector);

	if (get_dot_product(ray, pl->vector) == 0.0)
	{
		if (get_dot_product(temp_vector, pl->vector) == 0.0)
			printf("ray is contained in the plane");
		else
			printf("ray and plane are parallel\n");
	}
	inter = (t_inter *)malloc(sizeof(t_inter));
	inter->obj = (void *)pl;
	inter->type = PLANE;
	inter->distance = t;
	inter->point = set_coord(cam.point.x + t * ray.x, cam.point.y + t * ray.y, cam.point.z + t * ray.z);
	inter_to_light = make_vector(inter->point, lightpoint);
	inter->dist_to_light = get_dot_product(inter_to_light, inter_to_light);
	inter->next = NULL;
	return (inter);
}

t_inter *cylinder_intersections(t_coord ray, t_camera cam, t_cylinder *cy)
{
	(void)ray;
	(void)cam;
	(void)cy;

	// 1. find plane in point cy->point that is perpendicular to cy->vector
	// 2. point is in the middle and we represent a circle in that plane with function x^2 + y^2 = cy->d/2
	// 3. move this circle along this vector up and down by cy->height/2

	
	return (NULL);
}