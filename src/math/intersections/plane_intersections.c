/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_intersections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpiarova <zpiarova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 12:05:12 by zpiarova          #+#    #+#             */
/*   Updated: 2025/05/09 16:45:34 by zpiarova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minirt.h"

// params: Q = given point in plane, P = intersection point, n = surface normal
// equation for any point in plane: (P - Q ) * n = 0
// equation for any point in ray: P = C + t * ray 
// combined: t = - ((Q - C) o n) / (ray o n)
// t = ((point in plane - point on line=camera) o normal) / (ray o normal)
// t = parameter applied to ray that tells how far to move along direction
t_inter	*find_plane_inters(t_coord ray, t_coord origin, t_plane *pl)
{
	t_inter	*inter;
	t_coord	to_plane;
	float	denom;
	float	t;

	inter = NULL;
	to_plane = make_vector(origin, pl->point);
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
	{
		inter = make_inter((void *)pl, t, ray, origin);
		set_id_colour_type(inter, pl->id, PLANE, pl->colour);
	}
	return (inter);
}
