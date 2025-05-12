/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_intersections.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zuzanapiarova <zuzanapiarova@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 12:04:40 by zpiarova          #+#    #+#             */
/*   Updated: 2025/05/12 11:36:51 by zuzanapiaro      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minirt.h"

// accept the ray, ray origin, and sphere
// returns the intersection points - but not inters yet 
t_roots find_sphere_inter_roots(t_coord ray, t_coord origin, t_sphere *sp)
{
	t_coord	cam_to_sp;
	float	a;
	float	b;
	float	c;
	t_roots	roots;

	cam_to_sp = make_vector(sp->centre, origin);
	a = get_dot_product(ray, ray);
	b = 2 * get_dot_product(cam_to_sp, ray);
	c = get_dot_product(cam_to_sp, cam_to_sp) - pow((sp->diameter) / 2, 2);
	roots = find_roots(a, b, c);
	return(roots);
}

// based on parametric equations for sphere and ray
// any point in ray: P = C + t*ray
// any point in sphere: |P−C|=r --> sqrt(P-C o P - C) = r --> (P-c)o(P-C) = r^2
// accepts ray and ray origin, and object
// @returns intersection distance of ray with object - but not inter point yet
t_inter	*find_sphere_inters(t_coord ray, t_coord origin, t_sphere *sp)
{
	t_inter	*inter1;
	t_inter	*inter2;
	t_roots	roots;

	inter1 = NULL;
	inter2 = NULL;
	roots = find_sphere_inter_roots(ray, origin, sp);
	if (roots.t1 > EPSILON)
	{
		inter1 = make_inter((void *)sp, roots.t1, ray, origin);
		set_id_colour_type(inter1, sp->id, SPHERE, sp->colour);
	}
	if (roots.t2 > EPSILON && roots.t2 != roots.t1)
	{
		inter2 = make_inter((void *)sp, roots.t2, ray, origin);
		set_id_colour_type(inter2, sp->id, SPHERE, sp->colour);
	}
	return (return_object_inters(inter1, inter2));
}
