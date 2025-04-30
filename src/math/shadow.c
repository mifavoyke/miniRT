/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpiarova <zpiarova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 11:46:54 by zpiarova          #+#    #+#             */
/*   Updated: 2025/04/30 16:58:20 by zpiarova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

// inter_point ----> (hit?) ----> lightpoint

void debug_shadow_ray(t_coord ray_origin, t_coord ray_dir, t_sphere *sp, float t1, float t2, float max_distance)
{
	(void)sp;
	printf("SHADOW DEBUG:\n");
	printf("Ray origin:     (%f, %f, %f)\n", ray_origin.x, ray_origin.y, ray_origin.z);
	printf("Ray direction:  (%f, %f, %f)\n", ray_dir.x, ray_dir.y, ray_dir.z);
	// printf("  Sphere center:  (%f, %f, %f)\n", sp->centre.x, sp->centre.y, sp->centre.z);
	// printf("  Sphere radius:  %f\n", sp->diameter / 2.0);
	printf("t1 = %f, t2 = %f\n", t1, t2);
	printf("max_distance:   %f\n", max_distance);
}

bool does_ray_intersect_sphere(t_coord ray_origin, t_coord ray_dir, t_sphere *sp, float max_distance) // replace with Zuzka's function
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

bool does_ray_intersect_cylinder(t_coord ray_origin, t_coord ray_dir, t_cylinder *cy, float max_distance) // replace with Zuzka's function
{
	t_coord oc = make_vector(cy->centre, ray_origin);
	float radius = cy->diameter / 2.0;
	float dir_dot_axis = get_dot_product(ray_dir, cy->vector);
	float oc_dot_axis = get_dot_product(oc, cy->vector);
	t_coord d_proj = subtract_vectors(ray_dir, multiply_vector_by_constant(cy->vector, dir_dot_axis));
	t_coord oc_proj = subtract_vectors(oc, multiply_vector_by_constant(cy->vector, oc_dot_axis));
	float a = get_dot_product(d_proj, d_proj);
	float b = 2.0 * get_dot_product(d_proj, oc_proj);
	float c = get_dot_product(oc_proj, oc_proj) - radius * radius;
	float discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (false);
	float sqrt_d = sqrtf(discriminant);
	float t1 = (-b - sqrt_d) / (2 * a);
	float t2 = (-b + sqrt_d) / (2 * a);

	// Check bounds and height limits
	t_coord p1 = add_vectors(ray_origin, multiply_vector_by_constant(ray_dir, t1)); // break this down in a separate ft
	t_coord p2 = add_vectors(ray_origin, multiply_vector_by_constant(ray_dir, t2));
	float h1 = get_dot_product(make_vector(cy->centre, p1), cy->vector);
	float h2 = get_dot_product(make_vector(cy->centre, p2), cy->vector);
	if ((t1 > 0.001 && t1 < max_distance && fabs(h1) <= cy->height / 2) || (t2 > 0.001 && t2 < max_distance && fabs(h2) <= cy->height / 2))
		return (true);
	return (false);
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

int is_in_shadow(t_minirt *minirt, t_light_math *light_inputs, int current_id)
{
	float t;
	t_plane *tmp_pl;
	t_sphere *tmp_sp;
	t_cylinder *tmp_cy;

	tmp_sp = minirt->scene->sp;
	while (tmp_sp)
	{
		if (tmp_sp->id == current_id)
			return (0);
		if (does_ray_intersect_sphere(light_inputs->shadow_origin, light_inputs->shadow_ray, tmp_sp, light_inputs->max_length)) // replace with Zuzka's function
			return (1);
		tmp_sp = tmp_sp->next;
	}
	tmp_pl = minirt->scene->pl;
	while (tmp_pl)
	{
		t = get_plane_inter(light_inputs->shadow_ray, light_inputs->shadow_origin, tmp_pl);
		if (t > 0.001 && t < light_inputs->max_length)
			return (1);
		tmp_pl = tmp_pl->next;
	}
	tmp_cy = minirt->scene->cy;
	while (tmp_cy)
	{
		if (tmp_cy->id != current_id && does_ray_intersect_cylinder(light_inputs->shadow_origin, light_inputs->shadow_ray, tmp_cy, light_inputs->max_length)) // replace with Zuzka's function
			return (1);
		tmp_cy = tmp_cy->next;
	}
	return (0);
}