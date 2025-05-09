/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_intersections.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpiarova <zpiarova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 10:47:46 by zpiarova          #+#    #+#             */
/*   Updated: 2025/05/09 14:28:50 by zpiarova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minirt.h"

// there can be 2 coat intersections d1, d2
t_inter *get_coat_inters(t_scene *scene, t_coord base_ray_vector, t_coord ray_axis_cross, float root_part, t_cylinder *cy, t_coord ray)
{
	float	t1;
	float	t2;
	float	d1;
	float	d2;
	t_inter	*inter1;
	t_inter	*inter2;

	inter1 = NULL;
	inter2 = NULL;
	d1 = (get_dot_product(ray_axis_cross, get_cross_product(base_ray_vector, cy->vector)) + sqrt(root_part)) / get_dot_product(ray_axis_cross, ray_axis_cross);
	t1 = get_dot_product(cy->vector, subtract_vectors(multiply_vector_by_constant(ray, d1), base_ray_vector));
	if (d1 > EPSILON && t1 >= EPSILON && t1 <= (cy->height))
	{
		inter1 = make_inter((void *)cy, d1, ray, scene);
		set_id_colour_type(inter1, cy->id, CYLINDER, cy->colour);
	}
	d2 = (get_dot_product(ray_axis_cross, get_cross_product(base_ray_vector, cy->vector)) - sqrt(root_part)) / get_dot_product(ray_axis_cross, ray_axis_cross);	
	t2 = get_dot_product(cy->vector, subtract_vectors(multiply_vector_by_constant(ray, d2), base_ray_vector));
	if (d2 > EPSILON && t2 >= EPSILON && t2 <= (cy->height))
	{
		inter2 = make_inter((void *)cy, d2, ray, scene);
		set_id_colour_type(inter2, cy->id, CYLINDER, cy->colour);
	}
	return (return_object_inters(inter1, inter2));
}

// if ray is not parallel with the caps, check the intersection
// can intersect one or both caps - bottom/top
// only points on the cap planes within radius of cylinder are included
// for each we have distance d and t - what is t ???? 
t_inter	*get_cap_inters(t_coord ray, t_scene *scene, t_coord base_ray_vector, t_cylinder *cy)
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
		{
			inter3 = make_inter((void *)cy, top_d, ray, scene);
			set_id_colour_type(inter3, cy->id, PLANE, cy->colour);
		}
		bottom_d = get_dot_product(cy->vector, (add_vectors(base_ray_vector, multiply_vector_by_constant(cy->vector, cy->height)))) / get_dot_product(cy->vector, ray);
		bottom_t = get_dot_product(subtract_vectors(multiply_vector_by_constant(ray, bottom_d), add_vectors(base_ray_vector, multiply_vector_by_constant(cy->vector, cy->height))), 
								subtract_vectors(multiply_vector_by_constant(ray, bottom_d), add_vectors(base_ray_vector, multiply_vector_by_constant(cy->vector, cy->height))));
		if (bottom_d > EPSILON && bottom_t < pow(cy->diameter / 2, 2) && bottom_t > EPSILON)
		{
			inter4 = make_inter((void *)cy, bottom_d, ray, scene);
			set_id_colour_type(inter4, cy->id, PLANE, cy->colour);
		}
	}
	return (return_object_inters(inter3, inter4));
}

// base_ray_vector = helper vector (b - c) where b os center of the base and c is point on the ray
// ray_axis_cross = helper vector (n x a) used multiple times
// cache often used values and check coat and caps intersections
t_inter *find_cylinder_inters(t_coord ray, t_scene *scene, t_cylinder *cy)
{
	t_inter	*coat_inters;
	t_inter	*caps_inters;
	float	root_part;
	t_coord	base_center;
	t_coord base_ray_vector;
	t_coord	ray_axis_cross;
	t_camera cam = scene->c;
	
	coat_inters = NULL;
	caps_inters = NULL;
	base_center = subtract_vectors(cy->centre, multiply_vector_by_constant(cy->vector, cy->height / 2));
	base_ray_vector = make_vector(cam.point, base_center);
	ray_axis_cross = get_cross_product(ray, cy->vector);
	root_part = get_dot_product(ray_axis_cross, ray_axis_cross) * pow(cy->diameter / 2, 2) - (get_dot_product(cy->vector, cy->vector) * (pow(get_dot_product(base_ray_vector, ray_axis_cross), 2)));
	if (fabsf(root_part) < EPSILON || fabsf(get_dot_product(ray_axis_cross, ray_axis_cross)) < EPSILON) // no intersection OR line is parallel to the axis
	{
		coat_inters = NULL; // there is no intersection with coat or the ray is contained in the coat
		caps_inters = get_cap_inters(ray, scene, base_ray_vector, cy); // there will probably be 0 or 2 cap intersections
	}	
	else
	{
		coat_inters = get_coat_inters(scene, base_ray_vector, ray_axis_cross, root_part, cy, ray); // there will be 1 or 2 caot intersections
		caps_inters = get_cap_inters(ray, scene, base_ray_vector, cy); // there will be 1 or 2 cap inters
	}		
	return (return_object_inters(coat_inters, caps_inters));
}
