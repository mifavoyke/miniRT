/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpiarova <zpiarova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 10:47:46 by zpiarova          #+#    #+#             */
/*   Updated: 2025/04/30 16:40:21 by zpiarova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

// allocates intersection node and fills it with required data
t_inter	*make_inter(void *obj, enum e_obj_t type, float t, t_coord ray, t_camera cam, t_colour colour, int id)
{
	t_inter	*inter;
	
	inter = (t_inter *)malloc(sizeof(t_inter));
	if (!inter)
		return (NULL);
	inter->type = type;
	inter->obj = obj;
	inter->distance = fabsf(t);
	inter->point = set_coord(
		cam.point.x + t * ray.x,
		cam.point.y + t * ray.y,
		cam.point.z + t * ray.z
		);
	inter->colour = colour;
	inter->id = id;
	inter->next = NULL;
	return (inter);
}

// returns intersection list for that specific object with one ray
// TODO: some of the inter may have a next, move to the end before appending 
t_inter	*return_object_inters(t_inter *in1, t_inter *in2)
{
	if (!in1 && !in2)
		return (NULL);
	if (in1)
	{
		append_node(in2, &in1);
		return (in1);
	}
	else if (in2)
		return (in2);
	return (NULL);
}

// based on parametric equations for sphere and ray
// any point in ray: P = C + t*ray
// any point in sphere: |P−C|=r --> sqrt(P-C o P - C) = r --> (P-c)o(P-C) = r^2
t_inter	*find_sphere_intersections(t_coord ray, t_camera cam, t_sphere *sp)
{
	t_inter			*inter1;
	t_inter			*inter2;
	t_quadr_coef	qc;
	t_coord			cam_to_sp;
	
	inter1 = NULL;
	inter2 = NULL;
	cam_to_sp = make_vector(sp->centre, cam.point);
	qc.a = get_dot_product(ray, ray);
	qc.b = 2 * get_dot_product(cam_to_sp, ray);
	qc.c = get_dot_product(cam_to_sp, cam_to_sp) - pow((sp->diameter) / 2, 2);
	find_roots(&qc);
	if (qc.t1 > 0)
		inter1 = make_inter((void *)sp, SPHERE, qc.t1, ray, cam, sp->colour, sp->id);
	if (qc.t2 > 0 && qc.t2 != qc.t1)
		inter2 = make_inter((void *)sp, SPHERE, qc.t2, ray, cam, sp->colour, sp->id);
	return (return_object_inters(inter1, inter2));
}

// returns the scalar t at which the ray intersects the plane
float	get_plane_inter(t_coord ray, t_coord cam_origin, t_plane *pl)
{
	t_coord	to_plane;
	float	denom;
	float	t;

	to_plane = make_vector(cam_origin, pl->point);
	denom = get_dot_product(ray, pl->vector);
	if (fabsf(denom) < 1e-6)
	{
		if (fabsf(get_dot_product(to_plane, pl->vector)) < 1e-6)
			t = 0.1;
		else
			t = -1;
	}
	t = get_dot_product(to_plane, pl->vector) / denom;
	return (t);
}

// params: Q = given point in plane, P = intersection point, n = surface normal
// equation for any point in plane: (P - Q ) * n = 0
// equation for any point in ray: P = C + t * ray 
// combined: t = - ((Q - C) o n) / (ray o n)
// t = ((point in plane - point on line=camera) o normal) / (ray o normal)
// t = parameter applied to ray that tells how far to move along direction
t_inter	*find_plane_intersections(t_coord ray, t_camera cam, t_plane *pl)
{
	float	t;
	t_inter	*inter;
	
	inter = NULL;
	t = get_plane_inter(ray, cam.point, pl);
	if (t > 0)
		inter = make_inter((void *)pl, PLANE, t, ray, cam, pl->colour, pl->id);
	return (inter);
}

t_inter *get_coat_intersections(t_camera cam, t_coord base_ray_vector, t_coord ray_axis_cross, float root_part, t_cylinder *cy, t_coord ray)
{
	float t1;
	float t2;
	float d1;
	float d2;

	t_inter *inter1 = NULL;
	t_inter *inter2 = NULL;
	
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
	return (return_object_inters(inter1, inter2));
}

t_inter *get_cap_intersections(t_coord ray, t_camera cam, t_coord base_ray_vector, t_cylinder *cy)
{
	float t3;
	float t4;
	float d3;
	float d4;
	t_inter *inter3 = NULL;
	t_inter *inter4 = NULL;
	// checking caps intersections if the ray is not parallel with them:
	if (get_dot_product(cy->vector, ray) != 0)
	{
		// check bottom cap intersection
		d3 = get_dot_product(cy->vector, base_ray_vector)/ get_dot_product(cy->vector, ray);
		t3 = get_dot_product(subtract_vectors(multiply_vector_by_constant(ray, d3), base_ray_vector), subtract_vectors(multiply_vector_by_constant(ray, d3), base_ray_vector));
		if (d3 > 0 && t3 < pow(cy->diameter / 2, 2) && t3 > 0)  // INTERSECTION WITH BOTTOM CAP
			inter3 = make_inter((void *)cy, PLANE, d3, ray, cam, cy->colour, cy->id);
			
		// check top cap intersection
		d4 = get_dot_product(cy->vector, (add_vectors(base_ray_vector, multiply_vector_by_constant(cy->vector, cy->height)))) / get_dot_product(cy->vector, ray);
		t4 = get_dot_product(subtract_vectors(multiply_vector_by_constant(ray, d4), add_vectors(base_ray_vector, multiply_vector_by_constant(cy->vector, cy->height))), 
								subtract_vectors(multiply_vector_by_constant(ray, d4), add_vectors(base_ray_vector, multiply_vector_by_constant(cy->vector, cy->height))));
		if (d4 > 0 && t4 < pow(cy->diameter / 2, 2) && t4 > 0)  // INTERSECTION WITH BOTTOM CAP
			inter4 = make_inter((void *)cy, PLANE, d4, ray, cam, cy->colour, cy->id);
	}
	return (return_object_inters(inter3, inter4));
}

// todo: when we are close to cylinder cap, it idapears but the cylinder coat stays - fix ! 
t_inter *find_cylinder_intersections(t_coord ray, t_camera cam, t_cylinder *cy)
{
	t_inter	*coat_inters;
	t_inter	*caps_inters;
	float	root_part;
	t_coord	base_center;
	t_coord base_ray_vector; // helper vector (b - c) where b os center of the base and c is point on the ray
	t_coord	ray_axis_cross; // helper vector (n x a) used multiple times
	
	coat_inters = NULL;
	caps_inters = NULL;
	base_center = subtract_vectors(cy->centre, multiply_vector_by_constant(cy->vector, cy->height / 2));
	base_ray_vector = make_vector(cam.point, base_center);
	ray_axis_cross = get_cross_product(ray, cy->vector);
	root_part = get_dot_product(ray_axis_cross, ray_axis_cross) * pow(cy->diameter / 2, 2) - (get_dot_product(cy->vector, cy->vector) * (pow(get_dot_product(base_ray_vector, ray_axis_cross), 2)));
	// check cylinder intersections
	if (fabsf(root_part) < 1e-6 || fabsf(get_dot_product(ray_axis_cross, ray_axis_cross)) < 1e-6) // no intersection OR line is parallel to the axis
	{
		coat_inters = NULL; // there is no intersection with coat or the ray is contained in the coat
		caps_inters = get_cap_intersections(ray, cam, base_ray_vector, cy); // there will probably be 0 or 2 cap intersections
	}	
	else
	{
		coat_inters = get_coat_intersections(cam, base_ray_vector, ray_axis_cross, root_part, cy, ray); // there will be 1 or 2 caot intersections
		caps_inters = get_cap_intersections(ray, cam, base_ray_vector, cy); // there will be 1 or 2 cap inters
	}		
	return (return_object_inters(coat_inters, caps_inters));
}
