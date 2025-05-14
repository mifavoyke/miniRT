/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_intersections.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zuzanapiarova <zuzanapiarova@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 10:47:46 by zpiarova          #+#    #+#             */
/*   Updated: 2025/05/14 08:56:37 by zuzanapiaro      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minirt.h"

float	get_tbcd(t_coord ray, t_coord base_ray_vector, float t, t_cylinder *cy)
{
	return (dot(subtract_vectors(mult_vector_by_c(ray, t),
				add_vectors(base_ray_vector, mult_vector_by_c(cy->axis, cy->h
					))), subtract_vectors(mult_vector_by_c(ray, t),
				add_vectors(base_ray_vector,
					mult_vector_by_c(cy->axis, cy->h)))));
}

// finds intersection with the infinite cylinder coat, possibly t1 and t2
// projection1,2 are projections of the intersection points onto cylinder axis
// to test whether those intersections are within h of the cylinder
// @retruns either both roots in t1 and t2 or just one root in t1
// rac = ray_axis_cross
// brv = base_ray_vector
t_roots	coat_inters(t_coord brv, t_coord rac, t_cylinder *cy, t_coord ray)
{
	float	t1;
	float	t2;
	float	root_part;
	float	projection;
	t_roots	roots;

	roots.t1 = -1;
	roots.t2 = -1;
	root_part = dot(rac, rac) * pow(cy->diameter / 2, 2) - (dot(cy->axis,
				cy->axis) * (pow(dot(brv, rac), 2)));
	t1 = (dot(rac, cross(brv, cy->axis))
			+ sqrt(root_part)) / dot(rac, rac);
	projection = dot(cy->axis,
			subtract_vectors(mult_vector_by_c(ray, t1), brv));
	if (t1 > EPS && projection >= EPS && projection <= (cy->h))
	{
		roots.t1 = t1;
		roots.type1 = CYLINDER;
	}
	t2 = (dot(rac, cross(brv, cy->axis)) - sqrt(root_part)) / dot(rac, rac);
	projection = dot(cy->axis,
			subtract_vectors(mult_vector_by_c(ray, t2), brv));
	if (t2 > EPS && projection >= EPS && projection <= (cy->h))
		set_cyl_roots(&roots, t1, t2, CYLINDER);
	return (roots);
}

// if ray is not parallel with the caps, check the intersection
// can intersect one or both caps - bottom/top
// only points on the cap planes within radius of cylinder are included
// for each we have distance d and t - what is t ???
// tcd = t_top_center_distance - distance from intersection to middle of axis
// bcd = t_bottom_center_distance -distance from intersection to middle of axis
// brv = base_ray_vector
t_roots	cap_inters(t_coord ray, t_coord brv, t_cylinder *cy)
{
	float	t_top;
	float	t_bottom;
	float	ttcd;
	float	tbcd;
	t_roots	roots;

	roots.t1 = -1;
	roots.t2 = -1;
	if (fabsf(dot(cy->axis, ray)) > EPS)
	{
		t_top = dot(cy->axis, brv) / dot(cy->axis, ray);
		ttcd = dot(subtract_vectors(mult_vector_by_c(ray, t_top), brv),
				subtract_vectors(mult_vector_by_c(ray, t_top), brv));
		if (t_top > EPS && ttcd < pow(cy->diameter / 2, 2) && ttcd > EPS)
		{
			roots.t1 = t_top;
			roots.type1 = PLANE;
		}
		t_bottom = dot(cy->axis, (add_vectors(brv, mult_vector_by_c(cy->axis,
							cy->h)))) / dot(cy->axis, ray);
		tbcd = get_tbcd(ray, brv, t_bottom, cy);
		if (t_bottom > EPS && tbcd < pow(cy->diameter / 2, 2) && tbcd > EPS)
			set_cyl_roots(&roots, t_top, t_bottom, PLANE);
	}
	return (roots);
}

// base_ray_vector = helper vector (b - c) - b=center of base, c=point on ray
// ray_axis_cross = helper vector (n x a) used multiple times
// cache often used values and check coat and caps intersections
// if ((root_part < 0.0f || fabsf(dot(ray_axis_cross, ray_axis_cross)) < EPS))
// --> means no intersection with coat OR line is parallel to the axis
// else there will be 1 or 2 coat intersections
t_roots	find_cylinder_inters_roots(t_coord ray, t_coord origin, t_cylinder *cy)
{
	float	root_part;
	t_coord	base_center;
	t_coord	base_ray_vector;
	t_coord	ray_axis_cross;
	t_roots	roots;

	base_center = subtract_vectors(cy->centre,
			mult_vector_by_c(cy->axis, cy->h / 2));
	base_ray_vector = make_vector(origin, base_center);
	ray_axis_cross = cross(ray, cy->axis);
	root_part = dot(ray_axis_cross, ray_axis_cross) * pow(cy->diameter / 2, 2)
		- (dot(cy->axis, cy->axis) * (pow(dot(base_ray_vector,
						ray_axis_cross), 2)));
	if ((root_part < 0.0f || fabsf(dot(ray_axis_cross, ray_axis_cross)) < EPS))
		roots = cap_inters(ray, base_ray_vector, cy);
	else
	{
		roots = coat_inters(base_ray_vector, ray_axis_cross, cy, ray);
		if (roots.t1 == -1 || roots.t2 == -1)
			final_cyl_roots(&roots, cap_inters(ray, base_ray_vector, cy));
	}
	return (roots);
}

t_inter	*find_cylinder_inters(t_coord ray, t_coord origin, t_cylinder *cy)
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
