/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhusieva <yhusieva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 11:46:54 by zpiarova          #+#    #+#             */
/*   Updated: 2025/05/20 16:14:24 by yhusieva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static int	is_sphere_in_shadow(t_scene *scene,
	t_light_math *light_inputs, int current_id)
{
	t_sphere	*tmp_sp;
	t_roots		roots;

	tmp_sp = scene->sp;
	while (tmp_sp)
	{
		if (tmp_sp->id == current_id)
			return (0);
		roots = find_sphere_inter_roots(light_inputs->shadow_ray,
				light_inputs->shadow_origin, tmp_sp);
		if ((roots.t1 > EPS && roots.t1 < light_inputs->max_length)
			|| (roots.t2 > EPS && roots.t2 < light_inputs->max_length))
			return (1);
		tmp_sp = tmp_sp->next;
	}
	return (0);
}

static int	is_plane_in_shadow(t_scene *scene,
	t_light_math *light_inputs, int current_id)
{
	t_plane	*tmp_pl;
	float	t;
	(void)current_id;

	tmp_pl = scene->pl;
	while (tmp_pl)
	{
		// if (tmp_pl->id == current_id)
		// 	return (0);
		t = get_plane_inter_root(light_inputs->shadow_ray,
				light_inputs->shadow_origin, tmp_pl);
		if (t > EPS && t < light_inputs->max_length)
			return (1);
		tmp_pl = tmp_pl->next;
	}
	return (0);
}

static int	is_cylinder_in_shadow(t_scene *scene,
	t_light_math *light_inputs, int current_id)
{
	t_cylinder	*tmp_cy;
	t_roots		roots;

	tmp_cy = scene->cy;
	while (tmp_cy)
	{
		if (tmp_cy->id == current_id)
			return (0);
		roots = find_cylinder_inters_roots(light_inputs->shadow_ray,
				light_inputs->shadow_origin, tmp_cy);
		if ((roots.t1 > EPS && roots.t1 < light_inputs->max_length)
			|| (roots.t2 > EPS && roots.t2 < light_inputs->max_length))
			return (1);
		tmp_cy = tmp_cy->next;
	}
	return (0);
}

int	is_in_shadow(t_scene *scene, t_light_math *light_inputs, int id)
{
	if (is_sphere_in_shadow(scene, light_inputs, id))
		return (1);
	if (is_plane_in_shadow(scene, light_inputs, id))
		return (1);
	if (is_cylinder_in_shadow(scene, light_inputs, id))
		return (1);
	return (0);
}
