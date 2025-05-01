/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpiarova <zpiarova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 10:47:46 by zpiarova          #+#    #+#             */
/*   Updated: 2025/05/01 16:18:45 by zpiarova         ###   ########.fr       */
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
	if (qc.t1 > EPSILON)
		inter1 = make_inter((void *)sp, SPHERE, qc.t1, ray, cam, sp->colour, sp->id);
	if (qc.t2 > EPSILON && qc.t2 != qc.t1)
		inter2 = make_inter((void *)sp, SPHERE, qc.t2, ray, cam, sp->colour, sp->id);
	return (return_object_inters(inter1, inter2));
}

// params: Q = given point in plane, P = intersection point, n = surface normal
// equation for any point in plane: (P - Q ) * n = 0
// equation for any point in ray: P = C + t * ray 
// combined: t = - ((Q - C) o n) / (ray o n)
// t = ((point in plane - point on line=camera) o normal) / (ray o normal)
// t = parameter applied to ray that tells how far to move along direction
t_inter	*find_plane_intersections(t_coord ray, t_camera cam, t_plane *pl)
{
	t_inter	*inter;
	t_coord	to_plane;
	float	denom;
	float	t;
	
	inter = NULL;
	to_plane = make_vector(cam.point, pl->point);
	denom = get_dot_product(ray, pl->vector);
	if (fabsf(denom) < EPSILON)
	{
		if (fabsf(get_dot_product(to_plane, pl->vector)) < EPSILON)
			t = 0.1;
		else
			t = -1;
	}
	t = get_dot_product(to_plane, pl->vector) / denom;
	if (t > 0)
		inter = make_inter((void *)pl, PLANE, t, ray, cam, pl->colour, pl->id);
	return (inter);
}

// there can be 2 coat intersections d1, d2
t_inter *get_coat_intersections(t_camera cam, t_coord base_ray_vector, t_coord ray_axis_cross, float root_part, t_cylinder *cy, t_coord ray)
{
	float t1;
	float t2;
	float d1;
	float d2;

	t_inter *inter1 = NULL;
	t_inter *inter2 = NULL;
		d1 = (get_dot_product(ray_axis_cross, get_cross_product(base_ray_vector, cy->vector)) + sqrt(root_part)) / get_dot_product(ray_axis_cross, ray_axis_cross);
	t1 = get_dot_product(cy->vector, subtract_vectors(multiply_vector_by_constant(ray, d1), base_ray_vector));
	if (d1 > EPSILON && t1 >= EPSILON && t1 <= (cy->height))
		inter1 = make_inter((void *)cy, CYLINDER, d1, ray, cam, cy->colour, cy->id);
	d2 = (get_dot_product(ray_axis_cross, get_cross_product(base_ray_vector, cy->vector)) - sqrt(root_part)) / get_dot_product(ray_axis_cross, ray_axis_cross);	
	t2 = get_dot_product(cy->vector, subtract_vectors(multiply_vector_by_constant(ray, d2), base_ray_vector));
	if (d2 > EPSILON && t2 >= EPSILON && t2 <= (cy->height))
		inter2 = make_inter((void *)cy, CYLINDER, d2, ray, cam, cy->colour, cy->id);
	return (return_object_inters(inter1, inter2));
}

// if ray is not parallel with the caps, check the intersection
// can intersect one or both caps - bottom/top
// only points on the cap planes within radius of cylinder are included
// for each we have distance d and t - what is t ???? 
t_inter	*get_cap_intersections(t_coord ray, t_camera cam, t_coord base_ray_vector, t_cylinder *cy)
{
	float	top_t;
	float	bottom_t;
	float	top_d;
	float	bottom_d;
	t_inter *inter3 = NULL;
	t_inter *inter4 = NULL;
	if (get_dot_product(cy->vector, ray) != 0)
	{
		top_d = get_dot_product(cy->vector, base_ray_vector)/ get_dot_product(cy->vector, ray);
		top_t = get_dot_product(subtract_vectors(multiply_vector_by_constant(ray, top_d), base_ray_vector), subtract_vectors(multiply_vector_by_constant(ray, top_d), base_ray_vector));
		if (top_d > EPSILON && top_t < pow(cy->diameter / 2, 2) && top_t > EPSILON)
			inter3 = make_inter((void *)cy, PLANE, top_d, ray, cam, cy->colour, cy->id);
		bottom_d = get_dot_product(cy->vector, (add_vectors(base_ray_vector, multiply_vector_by_constant(cy->vector, cy->height)))) / get_dot_product(cy->vector, ray);
		bottom_t = get_dot_product(subtract_vectors(multiply_vector_by_constant(ray, bottom_d), add_vectors(base_ray_vector, multiply_vector_by_constant(cy->vector, cy->height))), 
								subtract_vectors(multiply_vector_by_constant(ray, bottom_d), add_vectors(base_ray_vector, multiply_vector_by_constant(cy->vector, cy->height))));
		if (bottom_d > EPSILON && bottom_t < pow(cy->diameter / 2, 2) && bottom_t > EPSILON)
			inter4 = make_inter((void *)cy, PLANE, bottom_d, ray, cam, cy->colour, cy->id);
	}
	return (return_object_inters(inter3, inter4));
}

// base_ray_vector = helper vector (b - c) where b os center of the base and c is point on the ray
// ray_axis_cross = helper vector (n x a) used multiple times
// cache often used values and check coat and caps intersections
t_inter *find_cylinder_intersections(t_coord ray, t_camera cam, t_cylinder *cy)
{
	t_inter	*coat_inters;
	t_inter	*caps_inters;
	float	root_part;
	t_coord	base_center;
	t_coord base_ray_vector;
	t_coord	ray_axis_cross;
	
	coat_inters = NULL;
	caps_inters = NULL;
	base_center = subtract_vectors(cy->centre, multiply_vector_by_constant(cy->vector, cy->height / 2));
	base_ray_vector = make_vector(cam.point, base_center);
	ray_axis_cross = get_cross_product(ray, cy->vector);
	root_part = get_dot_product(ray_axis_cross, ray_axis_cross) * pow(cy->diameter / 2, 2) - (get_dot_product(cy->vector, cy->vector) * (pow(get_dot_product(base_ray_vector, ray_axis_cross), 2)));
	if (fabsf(root_part) < EPSILON || fabsf(get_dot_product(ray_axis_cross, ray_axis_cross)) < EPSILON) // no intersection OR line is parallel to the axis
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

t_inter *find_paraboloid_intersections(t_coord ray, t_camera cam, t_cylinder *cy)
{
	// paraboloid:
	t_coord axis = set_coord(0.0,0.0,1.0); // must be normalized
	float f = 1.0;// focal_point - distance from vertex to focus - defines how wide/narrow it is going to be
	t_coord vertex = set_coord(0,20,5);
	// float height = 20; // height from vertex to the bottom
	
	// getting the transformation matrix from world to local paraboloid axis - origin [0,0,0], z is (0,0,1)
	t_coord helper_vector = set_coord(0,1,0);
	if (are_parallel(helper_vector, axis))
		helper_vector = set_coord(1,0,0);
	
	t_matrix R;
	R.U = axis;
	R.R = get_cross_product(R.U, helper_vector);	
	normalize(&R.R);
	R.F = get_cross_product(R.R, R.U);
	normalize(&R.F);

	// transform the ray from world to paraboloid space by applying the transpose of matrix R
	// transpose of R is used to "bring a vector into that local frame
	// o' (origin in paraboloid space) = R(o - V)
	// d' (direction in paraboloid space) = Rd
	t_coord transformed_ray_direction = multiply_transpose(R, ray);
	t_coord transformed_ray_origin = multiply_transpose(R, make_vector(vertex, cam.point));

	float a;
	float b;
	float c;
	float D;
	float			t1;
	float			t2;
	t_inter	*inter1 = NULL;
	t_inter *inter2 = NULL;

	a = pow(transformed_ray_direction.x, 2) + pow(transformed_ray_direction.y, 2);
	b = (2 * transformed_ray_direction.x * transformed_ray_direction.x) + (2 * transformed_ray_direction.y * transformed_ray_direction.y) - (4 * f * transformed_ray_direction.z);
	c = pow(transformed_ray_origin.x, 2) + pow(transformed_ray_origin.y, 2) - (4 * f * transformed_ray_origin.z);
	D = pow(b, 2) - 4 * a * c;
	if (D > 0)
		return (NULL); // no intersection
	else if (D == 0)
	{
		t1 = -b + sqrt(D) / (2 * a);
		t2 = t1;
	}
	else
	{
		t1 = -b + sqrt(D) / (2 * a);
		t2 = -b - sqrt(D) / (2 * a);
	}
	if (t1 > EPSILON)
		inter1 = make_inter((void *)cy, CYLINDER, t2, ray, cam, cy->colour, cy->id);
	if (t2 > EPSILON && t2 != t1)
		inter2 = make_inter((void *)cy, CYLINDER, t2, ray, cam, cy->colour, cy->id);
	return (return_object_inters(inter1, inter2));
}
