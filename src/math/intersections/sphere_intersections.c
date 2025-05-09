/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_intersections.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpiarova <zpiarova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 12:04:40 by zpiarova          #+#    #+#             */
/*   Updated: 2025/05/09 16:52:58 by zpiarova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minirt.h"

// accept the ray, ray origin, and sphere
// returns the intersection points - but not inters yet 
t_roots fins_sphere_roots(t_coord ray, t_coord origin, t_sphere *sp)
{
	t_quadr_coef	qc;
	t_coord			cam_to_sp;

	cam_to_sp = make_vector(sp->centre, origin);
	qc.a = get_dot_product(ray, ray);
	qc.b = 2 * get_dot_product(cam_to_sp, ray);
	qc.c = get_dot_product(cam_to_sp, cam_to_sp) - pow((sp->diameter) / 2, 2);
	find_roots(&qc);
	
}

// based on parametric equations for sphere and ray
// any point in ray: P = C + t*ray
// any point in sphere: |P−C|=r --> sqrt(P-C o P - C) = r --> (P-c)o(P-C) = r^2
// rewrite this to accept the ray, ray origin, and return the intersection points - but not inters yet 
t_inter	*find_sphere_inters(t_coord ray, t_coord origin, t_sphere *sp)
{
	t_inter			*inter1;
	t_inter			*inter2;

	inter1 = NULL;
	inter2 = NULL;
	
	
	if (qc.t1 > EPSILON)
	{
		inter1 = make_inter((void *)sp, qc.t1, ray, origin);
		set_id_colour_type(inter1, sp->id, SPHERE, sp->colour);
	}
	if (qc.t2 > EPSILON && qc.t2 != qc.t1)
	{
		inter2 = make_inter((void *)sp, qc.t2, ray, origin);
		set_id_colour_type(inter2, sp->id, SPHERE, sp->colour);
	}
	return (return_object_inters(inter1, inter2));
}
