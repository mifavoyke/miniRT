/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zuzanapiarova <zuzanapiarova@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 11:46:54 by zpiarova          #+#    #+#             */
/*   Updated: 2025/05/12 11:29:21 by zuzanapiaro      ###   ########.fr       */
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

int is_in_shadow(t_scene *scene, t_light_math *light_inputs, int current_id)
{
	float t;
	t_plane *tmp_pl;
	t_cylinder *tmp_cy;
	t_sphere *tmp_sp;
	t_roots roots;

	tmp_sp = scene->sp;
	while (tmp_sp)
	{
		if (tmp_sp->id == current_id)
			return (0);
		roots = find_sphere_inter_roots(light_inputs->shadow_ray, light_inputs->shadow_origin, tmp_sp);
		if ((roots.t1 > EPSILON && roots.t1 < light_inputs->max_length) || (roots.t2 > EPSILON && roots.t2 < light_inputs->max_length))
			return (1);
		tmp_sp = tmp_sp->next;
	}
	tmp_pl = scene->pl;
	while (tmp_pl)
	{
		t = get_plane_inter_root(light_inputs->shadow_ray, light_inputs->shadow_origin, tmp_pl);
		if (t > EPSILON && t < light_inputs->max_length)
			return (1);
		tmp_pl = tmp_pl->next;
	}
	tmp_cy = scene->cy;
	while (tmp_cy)
	{
		if (tmp_cy->id == current_id)
			return (0);
		if (does_ray_intersect_cylinder(light_inputs->shadow_origin, light_inputs->shadow_ray, tmp_cy, light_inputs->max_length)) // replace with Zuzka's function
			return (1);
		tmp_cy = tmp_cy->next;
	}
	return (0);
}
