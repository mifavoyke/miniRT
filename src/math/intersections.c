/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpiarova <zpiarova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 10:47:46 by zpiarova          #+#    #+#             */
/*   Updated: 2025/04/30 11:52:41 by zpiarova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

t_inter *make_inter(void *obj, enum e_obj_t type, float t, t_coord ray, t_camera cam, t_colour colour, int id)
{
	t_inter *inter;
	
	inter = (t_inter *)malloc(sizeof(t_inter));
	if (!inter)
		return (NULL);
	inter->type = type;
	inter->obj = obj;
	inter->distance = fabsf(t);
	inter->point = set_coord(cam.point.x + t * ray.x, cam.point.y + t * ray.y, cam.point.z + t * ray.z);
	inter->colour = colour;
	inter->id = id;
	inter->next = NULL;
	return (inter);
}

// based on parametric equations for sphere and ray
// any point in ray: P = C + t*ray
// any point in sphere: |P−C|=r --> sqrt(P-C o P - C) = r --> (P-c)o(P-C) = r^2
t_inter *find_sphere_intersections(t_coord ray, t_camera cam, t_sphere *sp)
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
		t1 = (-b + sqrt(discriminant)) / 2 * a;
		t2 = t1;
	}
	else // 2 solutions - in t1 enters and in t2 leaves
	{
		t1 = (-b + sqrt(discriminant)) / 2 * a;
		t2 = (-b - sqrt(discriminant)) / 2 * a;
	}
	// finding intersection points
	if (t1 < 0) // logical condition = point is behind the camera
		inter1 = NULL;
	else if (t1 < 1) // logical condition = point is between camera and viewport - consider it as we do not see it , can change 1 to 0, that means it is behind the camera
		inter1 = NULL; // TODO: change 1 to viewport->distance
	else
		inter1 = make_inter((void *)sp, SPHERE, t1, ray, cam, sp->colour, sp->id);

	if (t2 < 1 || t2 == t1) // TODO: change 1 to viewport->distance
		inter2 = NULL;
	else
		inter2 = make_inter((void *)sp, SPHERE, t2, ray, cam, sp->colour, sp->id);

	// return intersections that are in front of the camera
	if (inter1 && inter2)
		inter1->next = inter2;
	if (inter1)
		return (inter1);
	if (inter2)
		return (inter2);
	return (NULL);
}

// returns the scalar t at which the ray intersects the plane
float get_plane_intersection_t(t_coord ray, t_coord cam_origin, t_plane *pl)
{
	t_coord to_plane;
	float denom;
	float t;

	to_plane = make_vector(cam_origin, pl->point);
	denom = get_dot_product(ray, pl->vector);
	if (fabsf(denom) < 1e-6) // remove it ?
	{
		if (get_dot_product(to_plane, pl->vector) == 0.0)
			t = 0.1;
		else
			t = -1;
	}
	t = get_dot_product(to_plane, pl->vector) / denom;
	return (t);
}

// any point in plane: (P - Q ) * n = 0 --> Q = given point in plane, P = intersection point, n = surface normal
// any point in ray: P = C + t * ray 
// t = - ((Q - C) o n) / (ray o n)
// t = ((point in plane - point on line=camera) o normal) / (ray o normal)
t_inter *find_plane_intersections(t_coord ray, t_camera cam, t_plane *pl)
{
	float t; // parameter applied to the ray = scalar that tells you how far to move along the direction vector (ray) starting from the camera
	t_inter *inter;
	// t_coord temp_vector;

	// temp_vector = make_vector(cam.point, pl->point);
	// t = get_dot_product(temp_vector, pl->vector) / get_dot_product(ray, pl->vector); // why is there a minus?
	// // edge cases
	// if (get_dot_product(ray, pl->vector) == 0.0)
	// {
	// 	if (get_dot_product(temp_vector, pl->vector) == 0.0) // ray is contained in the plane
	// 		t = 0.1; // TODO: may change this - this is handling edge case when the plane goes straight through ray - they are contained
	// 	else // ray and plane are parallel, never interect
	// 		t = -1;
	// }
	t = get_plane_intersection_t(ray, cam.point, pl);
	if (t <= 0)
		inter = NULL;
	else 
		inter = make_inter((void *)pl, PLANE, t, ray, cam, pl->colour, pl->id);
	return (inter);
}

// t_inter *check_coat_intersections(t_coord base_ray_vector, t_coord ray, t_camera cam, t_cylinder *cy)
// {
// 	float d1;
// 	float d2;
// 	float t1;
// 	float t2;
// 	float root_part;
// 	t_inter *inter1 = NULL;
// 	t_inter *inter2 = NULL;
// 	t_coord ray_axis_cross; // helper vector (n x a) used multiple times

// 	ray_axis_cross = get_cross_product(ray, cy->vector);
// 	root_part = get_dot_product(ray_axis_cross, ray_axis_cross) * pow(cy->diameter / 2, 2) - (get_dot_product(cy->vector, cy->vector) * (pow(get_dot_product(base_ray_vector, ray_axis_cross), 2)));
	
// 	if (get_dot_product(ray_axis_cross, ray_axis_cross) == 0) // line is parallel to the axis // if rppt_part < 0, there is no intersection, else intersection is the entire ray
// 		return (NULL);
// 	d1 = (get_dot_product(ray_axis_cross, get_cross_product(base_ray_vector, cy->vector)) + sqrt(root_part)) / get_dot_product(ray_axis_cross, ray_axis_cross);
// 	if (d1 > 1)
// 	{
// 		t1 = get_dot_product(cy->vector, subtract_vectors(multiply_vector_by_constant(ray, d1), base_ray_vector));
// 		if (t1 >= 0 && t1 <= (cy->height))
// 			inter1 = make_inter((void *)cy, CYLINDER, d1, ray, cam, cy->colour, cy->id);
// 	}
	
// 	d2 = (get_dot_product(ray_axis_cross, get_cross_product(base_ray_vector, cy->vector)) - sqrt(root_part)) / get_dot_product(ray_axis_cross, ray_axis_cross);	
// 	if (d2 > 1)
// 	{
// 		t2 = get_dot_product(cy->vector, subtract_vectors(multiply_vector_by_constant(ray, d2), base_ray_vector));
// 		if (t2 >= 0 && t2 <= (cy->height))
// 			inter2 = make_inter((void *)cy, CYLINDER, d2, ray, cam, cy->colour, cy->id);
// 	}
	
// 	if (inter1 && inter2)
// 		inter1->next = inter2;
// 	if (inter1)
// 		return (inter1);
// 	if (inter2)
// 		return (inter2);
// 	return (NULL);
// }

// t_inter *get_caps_intersections(t_cylinder *cy, t_coord ray, t_coord base_ray_vector, t_camera cam)
// {
// 	float t1;
// 	float t2;
// 	float d1;
// 	float d2;
// 	t_inter *inter1 = NULL;
// 	t_inter *inter2 = NULL;
	
// 	// if ray is parallel to end caps, we do not render them --> NULL
// 	if (get_dot_product(cy->vector, ray) == 0)
// 		return (NULL);
// 	// check bottom cap intersection
// 	d1 = get_dot_product(cy->vector, base_ray_vector)/ get_dot_product(cy->vector, ray);
// 	if (d1 > 1)
// 	{
// 		t1 = get_dot_product(subtract_vectors(multiply_vector_by_constant(ray, d1), base_ray_vector), subtract_vectors(multiply_vector_by_constant(ray, d1), base_ray_vector));
// 		if (t1 < pow(cy->diameter / 2, 2) && t1 > 0)
// 			inter1 = make_inter((void *)cy, PLANE, d1, ray, cam, cy->colour, cy->id);
// 	}
		
// 	// check top cap intersection
// 	d2 = get_dot_product(cy->vector, (add_vectors(base_ray_vector, multiply_vector_by_constant(cy->vector, cy->height)))) / get_dot_product(cy->vector, ray);
// 	if (d2 > 1)
// 	{
// 		t2 = get_dot_product(subtract_vectors(multiply_vector_by_constant(ray, d2), add_vectors(base_ray_vector, multiply_vector_by_constant(cy->vector, cy->height))), 
// 								subtract_vectors(multiply_vector_by_constant(ray, d2), add_vectors(base_ray_vector, multiply_vector_by_constant(cy->vector, cy->height))));
// 		if (t2 < pow(cy->diameter / 2, 2) && t2 > 0)
// 			inter2 = make_inter((void *)cy, PLANE, d2, ray, cam, cy->colour, cy->id);
// 	}

// 	if (inter1 && inter2)
// 		inter1->next = inter2;
// 	if (inter1)
// 		return (inter1);
// 	if (inter2)
// 		return (inter2);
// 	return (NULL);
// }

// any point in ray: P = C + t*ray
// cylinder is defined by distance to its axis, not to a point or a plane, unlike a sphere
// cylinder is defined by all points that are at a fixed distance r from the cylinder’s axis
// to check whether a point lies on the cylinder surface, you need to find how far it is from the axis (not from a point)
// but in 3D, this “distance to a line” is hard to work with directly — so we project everything onto the plane perpendicular to the axis
// project both the ray(helper 2) and vector from the cylinder axis to the ray origin(helper 1) onto the plane perpendicular to the cylinder’s axis
// then the problem becomes 2D problem of a line intersecting a circle of radius r

// cylinder coat: || a x (p - b) || = r -> a=axis vector, b=cylinder base center, p=any point on coat
// cylinder height: 0 <= a o (p - b) <= h
// line: t = c + n*d  -> c=point on line, n=line unit vector, d=distance 
// t = a o (c + n*d - b)
// 1. solve for d
// Solving for d only gives you the distance at which the line intersects the infinite cylinder
// To see if the intersection occurs within the part we consider the actual cylinder, we need to check if
// the signed distance t from the cylinder base b along the axis a to the intersection p is within -h/2 and h/2 cylinder
// 2. solve for t - t means how far along the cylinder axis the point is
// --> -h/2 <= t <= h/2
// 3. find caps intersections
// todo: when we are close to cylinder cap, it idapears but the cylinder coat stays - fix ! 
t_inter *find_cylinder_intersections(t_coord ray, t_camera cam, t_cylinder *cy)
{
	float root_part;
	float t1;
	float t2;
	float t3;
	float t4;
	float d1;
	float d2;
	float d3;
	float d4;
	t_inter *inter1 = NULL;
	t_inter *inter2 = NULL;
	t_inter *inter3 = NULL;
	t_inter *inter4 = NULL;
	t_coord base_center; // 
	t_coord ray_axis_cross; // helper vector (n x a) used multiple times
	t_coord base_ray_vector; // helper vector (b - c) where b os center of the base and c is point on the ray
	
	//base_center = add_vectors(cy->centre, multiply_vector_by_constant(cy->vector, -(cy->height / 2)));
	base_center = subtract_vectors(cy->centre, multiply_vector_by_constant(cy->vector, cy->height / 2));
	ray_axis_cross = get_cross_product(ray, cy->vector);
	base_ray_vector = make_vector(cam.point, base_center);
	root_part = get_dot_product(ray_axis_cross, ray_axis_cross) * pow(cy->diameter / 2, 2) - (get_dot_product(cy->vector, cy->vector) * (pow(get_dot_product(base_ray_vector, ray_axis_cross), 2)));
	
	// check cylinder intersections
	if (root_part < 0) // no intersection
	{
		d1 = 0;
		d2 = 0;	
	}	
	if (get_dot_product(ray_axis_cross, ray_axis_cross) == 0) // line is parallel to the axis
	{
		if (root_part < 0) // no intersection
		{
			d1 = 0;
			d2 = 0;	
		}
		else // intersection is the entire line
		{
			d1 = 1; // idk, for now
			d2 = 1; // idk, for now
		}
	}
	else
	{
		// first coat intersection
		d1 = (get_dot_product(ray_axis_cross, get_cross_product(base_ray_vector, cy->vector)) + sqrt(root_part)) / get_dot_product(ray_axis_cross, ray_axis_cross);
		t1 = get_dot_product(cy->vector, subtract_vectors(multiply_vector_by_constant(ray, d1), base_ray_vector));
		if (d1 > 0 && t1 >= 0 && t1 <= (cy->height))  // INTERSECTION WITH COAT
			inter1 = make_inter((void *)cy, CYLINDER, d1, ray, cam, cy->colour, cy->id);
		
		// second coat intersection
		d2 = (get_dot_product(ray_axis_cross, get_cross_product(base_ray_vector, cy->vector)) - sqrt(root_part)) / get_dot_product(ray_axis_cross, ray_axis_cross);	
		t2 = get_dot_product(cy->vector, subtract_vectors(multiply_vector_by_constant(ray, d2), base_ray_vector));
		if (d2 > 0 && t2 >= 0 && t2 <= (cy->height)) 	// INTERSECTION WITH COAT
			inter2 = make_inter((void *)cy, CYLINDER, d2, ray, cam, cy->colour, cy->id);
	}

	// checking caps intersections if the ray is not parallel with them:
	if (get_dot_product(cy->vector, ray) != 0)
	{
		// check bottom cap intersection
		d3 = get_dot_product(cy->vector, base_ray_vector)/ get_dot_product(cy->vector, ray);
		t3 = get_dot_product(subtract_vectors(multiply_vector_by_constant(ray, d3), base_ray_vector), subtract_vectors(multiply_vector_by_constant(ray, d3), base_ray_vector));
		if (d1 > 0 && t3 < pow(cy->diameter / 2, 2) && t3 > 0)  // INTERSECTION WITH BOTTOM CAP
			inter3 = make_inter((void *)cy, PLANE, d3, ray, cam, cy->colour, cy->id);
			
		// check top cap intersection
		d4 = get_dot_product(cy->vector, (add_vectors(base_ray_vector, multiply_vector_by_constant(cy->vector, cy->height)))) / get_dot_product(cy->vector, ray);
		t4 = get_dot_product(subtract_vectors(multiply_vector_by_constant(ray, d4), add_vectors(base_ray_vector, multiply_vector_by_constant(cy->vector, cy->height))), 
							 subtract_vectors(multiply_vector_by_constant(ray, d4), add_vectors(base_ray_vector, multiply_vector_by_constant(cy->vector, cy->height))));
		if (d2 > 0 && t4 < pow(cy->diameter / 2, 2) && t4 > 0)  // INTERSECTION WITH BOTTOM CAP
			inter4 = make_inter((void *)cy, PLANE, d4, ray, cam, cy->colour, cy->id);
	}
			
	// return intersections that are in front of the camera
	if (inter1)
	{
		if (inter2)
			inter1->next = inter2;
		if (inter3)
			inter1->next = inter3;
		if (inter4)
			inter1->next = inter4;
		return (inter1);
	}
	if (inter2)
	{
		if (inter3)
			inter2->next = inter3;
		if (inter4)
			inter2->next = inter4;
		return (inter2);
	}
	if (inter3)
	{
		if (inter4)
			inter3->next = inter4;
		return (inter3);
	}
	if (inter4)
		return (inter4);
	return (NULL);
}