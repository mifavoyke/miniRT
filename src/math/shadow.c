/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhusieva <yhusieva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 11:46:54 by zpiarova          #+#    #+#             */
/*   Updated: 2025/05/09 14:04:46 by yhusieva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

float vector_length_squared(t_coord v)
{
	return get_dot_product(v, v);
}

int does_ray_intersect_cylinder(t_coord origin, t_coord dir, t_cylinder *cy, float max_len)
{
	t_coord base_center = subtract_vectors(cy->centre, multiply_vector_by_constant(cy->vector, cy->height / 2));
	t_coord base_ray_vec = subtract_vectors(base_center, origin);
	t_coord ray_axis_cross = get_cross_product(dir, cy->vector);
	float dot_cross = get_dot_product(ray_axis_cross, ray_axis_cross);
	float root_part = dot_cross * pow(cy->diameter / 2, 2) - get_dot_product(cy->vector, cy->vector) * pow(get_dot_product(base_ray_vec, ray_axis_cross), 2);
	// ===== Check coat intersections =====
	if (fabsf(root_part) > EPSILON && fabsf(dot_cross) > EPSILON)
	{
		float d1 = (get_dot_product(ray_axis_cross, get_cross_product(base_ray_vec, cy->vector)) + sqrtf(root_part)) / dot_cross;
		t_coord hit1 = add_vectors(origin, multiply_vector_by_constant(dir, d1));
		float t1 = get_dot_product(cy->vector, subtract_vectors(hit1, base_center));
		if (d1 > EPSILON && d1 < max_len && t1 >= 0 && t1 <= cy->height)
			return 1;

		float d2 = (get_dot_product(ray_axis_cross, get_cross_product(base_ray_vec, cy->vector)) - sqrtf(root_part)) / dot_cross;
		t_coord hit2 = add_vectors(origin, multiply_vector_by_constant(dir, d2));
		float t2 = get_dot_product(cy->vector, subtract_vectors(hit2, base_center));
		if (d2 > EPSILON && d2 < max_len && t2 >= 0 && t2 <= cy->height)
			return 1;
	}
	// ===== Check cap intersections =====
	if (get_dot_product(cy->vector, dir) != 0)
	{
		// Top cap
		float top_d = get_dot_product(cy->vector, subtract_vectors(base_center, origin)) / get_dot_product(cy->vector, dir);
		if (top_d > EPSILON && top_d < max_len)
		{
			t_coord top_hit = add_vectors(origin, multiply_vector_by_constant(dir, top_d));
			if (vector_length_squared(subtract_vectors(top_hit, base_center)) < pow(cy->diameter / 2, 2))
				return 1;
		}
		// Bottom cap
		t_coord top_center = add_vectors(base_center, multiply_vector_by_constant(cy->vector, cy->height));
		float bot_d = get_dot_product(cy->vector, subtract_vectors(top_center, origin)) / get_dot_product(cy->vector, dir);
		if (bot_d > EPSILON && bot_d < max_len)
		{
			t_coord bot_hit = add_vectors(origin, multiply_vector_by_constant(dir, bot_d));
			if (vector_length_squared(subtract_vectors(bot_hit, top_center)) < pow(cy->diameter / 2, 2))
				return 1;
		}
	}
	return 0;
}

// returns the scalar t at which the ray intersects the plane
float get_plane_inter(t_coord ray, t_coord cam_origin, t_plane *pl)
{
	t_coord to_plane;
	float denom;
	float t;

	to_plane = make_vector(cam_origin, pl->point);
	denom = get_dot_product(ray, pl->vector);
	if (fabsf(denom) < EPSILON)
	{
		if (fabsf(get_dot_product(to_plane, pl->vector)) < EPSILON)
			t = 0.1;
		else
			t = -1;
	}
	t = get_dot_product(to_plane, pl->vector) / denom;
	return (t);
}

bool does_ray_intersect_sphere(t_coord ray_origin, t_coord ray_dir, t_sphere *sp, float max_distance)
{
	t_coord oc = make_vector(ray_origin, sp->centre);
	float radius = sp->diameter / 2.0;
	float a = get_dot_product(ray_dir, ray_dir);
	float b = 2.0 * get_dot_product(oc, ray_dir);
	float c = get_dot_product(oc, oc) - radius * radius;
	float discriminant = b * b - 4 * a * c;

	if (discriminant <= 0)
		return (false);
	float sqrt_d = sqrtf(discriminant);
	float t1 = fabs((-b - sqrt_d) / (2 * a));
	float t2 = fabs((-b + sqrt_d) / (2 * a));
	if ((t1 > 0.001 && t1 < max_distance) || (t2 > 0.001 && t2 < max_distance))
		return (true);
	return (false);
}

// int does_ray_intersect_sphere(t_coord origin, t_coord target, t_sphere *sp, float max_dist)
// {
// 	t_quadr_coef	qc;
// 	t_coord ray;
// 	t_coord origin_to_sp;
	
// 	ray = make_vector(origin, target);
// 	origin_to_sp = make_vector(origin, sp->centre);
// 	qc.a = get_dot_product(ray, ray);
// 	qc.b = 2 * get_dot_product(origin_to_sp, ray);
// 	qc.c = get_dot_product(origin_to_sp, origin_to_sp) - pow((sp->diameter) / 2, 2);
// 	find_roots(&qc);
// 	// qc.t1 = fabs(qc.t1);
// 	// qc.t2 = fabs(qc.t2);
// 	if ((qc.t1 > 0.001 && qc.t1 < max_dist) || (qc.t2 > 0.001 && qc.t2 < max_dist))
// 		return (1);
// 	return (0);
// }

int is_in_shadow(t_scene *scene, t_light_math *light_inputs, int current_id)
{
	float t;
	t_plane *tmp_pl;
	t_cylinder *tmp_cy;
	t_sphere *tmp_sp;

	tmp_sp = scene->sp;
	while (tmp_sp)
	{
		if (tmp_sp->id == current_id)
			return (0);
		if (does_ray_intersect_sphere(light_inputs->shadow_origin, light_inputs->shadow_ray, tmp_sp, light_inputs->max_length))
			return (1);
		tmp_sp = tmp_sp->next;
	}
	tmp_pl = scene->pl;
	while (tmp_pl)
	{
		t = get_plane_inter(light_inputs->shadow_ray, light_inputs->shadow_origin, tmp_pl);
		if (t > 0.001 && t < light_inputs->max_length)
			return (1);
		tmp_pl = tmp_pl->next;
	}
	tmp_cy = scene->cy;
	while (tmp_cy)
	{
		if (tmp_cy->id != current_id && does_ray_intersect_cylinder(light_inputs->shadow_origin, light_inputs->shadow_ray, tmp_cy, light_inputs->max_length)) // replace with Zuzka's function
			return (1);
		tmp_cy = tmp_cy->next;
	}
	return (0);
}
