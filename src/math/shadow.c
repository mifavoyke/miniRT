/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zuzanapiarova <zuzanapiarova@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 11:46:54 by zpiarova          #+#    #+#             */
/*   Updated: 2025/05/15 23:25:50 by zuzanapiaro      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

// id = current id 
static int	is_sphere_in_shadow(t_scene *scene, t_light_math *l_input, int id)
{
	t_sphere	*tmp_sp;
	t_roots		roots;

	tmp_sp = scene->sp;
	while (tmp_sp)
	{
		if (tmp_sp->id == id)
			return (0);
		roots = find_sphere_inter_roots(l_input->shadow_ray,
				l_input->shadow_origin, tmp_sp);
		if ((roots.t1 > EPS && roots.t1 < l_input->max_length)
			|| (roots.t2 > EPS && roots.t2 < l_input->max_length))
			return (1);
		tmp_sp = tmp_sp->next;
	}
	return (0);
}

static int	is_plane_in_shadow(t_scene *scene, t_light_math *l_input)
{
	t_plane	*tmp_pl;
	float	t;

	tmp_pl = scene->pl;
	while (tmp_pl)
	{
		t = get_plane_inter_root(l_input->shadow_ray,
				l_input->shadow_origin, tmp_pl);
		if (t > EPS && t < l_input->max_length)
			return (1);
		tmp_pl = tmp_pl->next;
	}
	return (0);
}

// id = current id 
static int	is_cylinder_in_shadow(t_scene *scene, t_light_math *l_input, int id)
{
	t_cylinder	*tmp_cy;
	t_roots		roots;

	tmp_cy = scene->cy;
	while (tmp_cy)
	{
		if (tmp_cy->id == id)
			return (0);
		roots = find_cylinder_inters_roots(l_input->shadow_ray,
				l_input->shadow_origin, tmp_cy);
		if ((roots.t1 > EPS && roots.t1 < l_input->max_length)
			|| (roots.t2 > EPS && roots.t2 < l_input->max_length))
			return (1);
		tmp_cy = tmp_cy->next;
	}
	return (0);
}

// returns 1 if object is in shadow,0 if not
int	is_in_shadow(t_scene *scene, t_light_math *l_input, int id)
{
	if (is_sphere_in_shadow(scene, l_input, id))
		return (1);
	if (is_plane_in_shadow(scene, l_input))
		return (1);
	if (is_cylinder_in_shadow(scene, l_input, id))
		return (1);
	return (0);
}
