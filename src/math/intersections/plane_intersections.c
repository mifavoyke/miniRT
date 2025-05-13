/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_intersections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zuzanapiarova <zuzanapiarova@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 12:05:12 by zpiarova          #+#    #+#             */
/*   Updated: 2025/05/13 12:33:16 by zuzanapiaro      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minirt.h"

// params: Q = given point in plane, P = intersection point, n = surface normal
// equation for any point in plane: (P - Q ) * n = 0
// equation for any point in ray: P = C + t * ray 
// combined: t = - ((Q - C) o n) / (ray o n)
// t = ((point in plane - point on line=camera) o normal) / (ray o normal)
// t = parameter applied to ray that tells how far to move along direction
// @returns intersection distance of ray with object - but not inter point yet
// or -1 in case of no inter/inter behind the camera 
float	get_plane_inter_root(t_coord ray, t_coord origin, t_plane *pl)
{
	t_coord	to_plane;
	float	denom;
	float	t;

	to_plane = make_vector(origin, pl->point);
	denom = dot(ray, pl->vector);
	if (fabsf(denom) < EPS)
	{
		if (fabsf(dot(to_plane, pl->vector)) < EPS)
			t = 0.1;
		else
			t = -1;
	}
	t = dot(to_plane, pl->vector) / denom;
	if (t >= 0)
		return (t);
	else
		return (-1);
}

// gets the inter deistance ffrom another function
// and creates and returns the intersection point with other info
t_inter	*find_plane_inters(t_coord ray, t_coord origin, t_plane *pl)
{
	t_inter	*inter;
	float	t;

	inter = NULL;
	t = get_plane_inter_root(ray, origin, pl);
	if (t >= 0)
	{
		inter = make_inter((void *)pl, t, ray, origin);
		set_id_colour_type(inter, pl->id, PLANE, pl->colour);
	}
	return (inter);
}
