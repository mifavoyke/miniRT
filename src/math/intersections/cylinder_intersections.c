/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_intersections.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zuzanapiarova <zuzanapiarova@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 10:47:46 by zpiarova          #+#    #+#             */
/*   Updated: 2025/05/13 10:26:15 by zuzanapiaro      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minirt.h"

// finds intersection with the infinite cylinder coat, possibly t1 and t2
// projection1,2 are projections of the intersection points onto the cylinder's axis
// to test whether those intersections are within height of the cylinder
// @retruns either both roots in t1 and t2 or just one root in t1
t_roots get_coat_inters(t_coord origin, t_coord base_ray_vector, t_coord ray_axis_cross, float root_part, t_cylinder *cy, t_coord ray)
{
	float	projection1;
	float	projection2;
	t_roots roots;
	float	t1;
	float	t2;
	(void) origin;
	// t_inter	*inter1;
	// t_inter	*inter2;

	// inter1 = NULL;
	// inter2 = NULL;
	roots.t1 = -1;
	roots.t2 = -1;
	t1 = (get_dot_product(ray_axis_cross, get_cross_product(base_ray_vector, cy->vector)) + sqrt(root_part)) / get_dot_product(ray_axis_cross, ray_axis_cross);
	projection1 = get_dot_product(cy->vector, subtract_vectors(multiply_vector_by_constant(ray, t1), base_ray_vector));
	if (t1 > EPSILON && projection1 >= EPSILON && projection1 <= (cy->height))
	{
		roots.t1 = t1;
		roots.type1 = CYLINDER;
		//inter1 = make_inter((void *)cy, roots.t1, ray, origin);
		//set_id_colour_type(inter1, cy->id, CYLINDER, cy->colour);
	}
	t2 = (get_dot_product(ray_axis_cross, get_cross_product(base_ray_vector, cy->vector)) - sqrt(root_part)) / get_dot_product(ray_axis_cross, ray_axis_cross);	
	projection2 = get_dot_product(cy->vector, subtract_vectors(multiply_vector_by_constant(ray, t2), base_ray_vector));
	if (t2 > EPSILON && projection2 >= EPSILON && projection2 <= (cy->height))
	{
		if (t2 != t1)
		{
			if (roots.t1 != -1)
			{
				roots.t2 = t2;
				roots.type2 = CYLINDER;
			}
			else
			{
				roots.t1 = t2;
				roots.type1 = CYLINDER;
			}
		}
		//inter2 = make_inter((void *)cy, roots.t2, ray, origin);
		//set_id_colour_type(inter2, cy->id, CYLINDER, cy->colour);
	}
	return (roots);
	//return (return_object_inters(inter1, inter2));
}

// if ray is not parallel with the caps, check the intersection
// can intersect one or both caps - bottom/top
// only points on the cap planes within radius of cylinder are included
// for each we have distance d and t - what is t ???
t_roots	get_cap_inters(t_coord ray, t_coord base_ray_vector, t_cylinder *cy)
{
	float	t_top_dist_from_center;
	float	t_bottom_dist_from_center;
	float	t_top;
	float	t_bottom;
	t_roots roots;
	// t_inter *inter3 = NULL;
	// t_inter *inter4 = NULL;

	roots.t1 = -1;
	roots.t2 = -1;
	if (fabsf(get_dot_product(cy->vector, ray)) < EPSILON)
	{
		t_top = get_dot_product(cy->vector, base_ray_vector)/ get_dot_product(cy->vector, ray);
		t_top_dist_from_center = get_dot_product(subtract_vectors(multiply_vector_by_constant(ray, t_top), base_ray_vector), subtract_vectors(multiply_vector_by_constant(ray, t_top), base_ray_vector));
		if (t_top > EPSILON && t_top_dist_from_center < pow(cy->diameter / 2, 2) && t_top_dist_from_center > EPSILON)
		{
			roots.t1 = t_top;
			roots.type1 = PLANE;
			// inter3 = make_inter((void *)cy, t_top, ray, origin);
			// set_id_colour_type(inter3, cy->id, PLANE, cy->colour);
		}
		t_bottom = get_dot_product(cy->vector, (add_vectors(base_ray_vector, multiply_vector_by_constant(cy->vector, cy->height)))) / get_dot_product(cy->vector, ray);
		t_bottom_dist_from_center = get_dot_product(subtract_vectors(multiply_vector_by_constant(ray, t_bottom), add_vectors(base_ray_vector, multiply_vector_by_constant(cy->vector, cy->height))), 
								subtract_vectors(multiply_vector_by_constant(ray, t_bottom), add_vectors(base_ray_vector, multiply_vector_by_constant(cy->vector, cy->height))));
		if (t_bottom > EPSILON && t_bottom_dist_from_center < pow(cy->diameter / 2, 2) && t_bottom_dist_from_center > EPSILON)
		{
			// inter4 = make_inter((void *)cy, t_bottom, ray, origin);
			// set_id_colour_type(inter4, cy->id, PLANE, cy->colour);
			if (t_bottom != t_top)
			{
				if (roots.t1 != -1)
				{
					roots.t2 = t_bottom;
					roots.type2 = PLANE;
				}
				else
				{
					roots.t1 = t_bottom;
					roots.type1 = PLANE;
				}
			}
		}
	}
	return (roots);
	//return (return_object_inters(inter3, inter4));
}

// base_ray_vector = helper vector (b - c) where b os center of the base and c is point on the ray
// ray_axis_cross = helper vector (n x a) used multiple times
// cache often used values and check coat and caps intersections
t_roots find_cylinder_inters_roots(t_coord ray, t_coord origin, t_cylinder *cy)
{
	// t_inter	*coat_inters;
	// t_inter	*caps_inters;
	float	root_part;
	t_coord	base_center;
	t_coord base_ray_vector;
	t_coord	ray_axis_cross;
	t_roots	roots;
	t_roots	helper;
	
	// coat_inters = NULL;
	// caps_inters = NULL;
	base_center = subtract_vectors(cy->centre, multiply_vector_by_constant(cy->vector, cy->height / 2));
	base_ray_vector = make_vector(origin, base_center);
	ray_axis_cross = get_cross_product(ray, cy->vector);
	root_part = get_dot_product(ray_axis_cross, ray_axis_cross) * pow(cy->diameter / 2, 2) - (get_dot_product(cy->vector, cy->vector) * (pow(get_dot_product(base_ray_vector, ray_axis_cross), 2)));
	if ((root_part < 0.0f || fabsf(get_dot_product(ray_axis_cross, ray_axis_cross)) < EPSILON)) // no intersection with coat OR line is parallel to the axis
	{
		// coat_inters = NULL; // there is no intersection with coat or the ray is contained in the coat
		roots = get_cap_inters(ray, base_ray_vector, cy);
		// caps_inters = get_cap_inters(ray, origin, base_ray_vector, cy); // there will probably be 0 or 2 cap intersections
	}	
	else
	{
		roots = get_coat_inters(origin, base_ray_vector, ray_axis_cross, root_part, cy, ray); // there will be 1 or 2 coat intersections
		if (roots.t2 == -1)
		{
			helper = get_cap_inters(ray, base_ray_vector, cy); // there will be 1 or 2 cap inters
			roots.t2 = helper.t1;
			roots.type2 = helper.type1;	
		}
		// coat_inters = get_coat_inters(origin, base_ray_vector, ray_axis_cross, root_part, cy, ray); // there will be 1 or 2 caot intersections
		// caps_inters = get_cap_inters(ray, origin, base_ray_vector, cy); // there will be 1 or 2 cap inters
	}	
	return (roots);	
	//return (return_object_inters(coat_inters, caps_inters));
}

t_inter *find_cylinder_inters(t_coord ray, t_coord origin, t_cylinder *cy)
{
	t_inter	*inter1;
	t_inter	*inter2;
	t_roots	roots;

	inter1 = NULL;
	inter2 = NULL;
	roots = find_cylinder_inters_roots(ray, origin, cy);
	if (roots.t1 != -1)
	{
		inter1 = make_inter((void *)cy, roots.t1, ray, origin);
		set_id_colour_type(inter1, cy->id, roots.type1, cy->colour);
	}
	if (roots.t2 != -1)
	{
		inter2 = make_inter((void *)cy, roots.t2, ray, origin);
		set_id_colour_type(inter2, cy->id, roots.type2, cy->colour);
	}	
	return (return_object_inters(inter1, inter2));
}
