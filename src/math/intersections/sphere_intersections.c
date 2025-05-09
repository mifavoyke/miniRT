/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_intersections.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpiarova <zpiarova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 12:04:40 by zpiarova          #+#    #+#             */
/*   Updated: 2025/05/09 13:38:17 by zpiarova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minirt.h"

// based on parametric equations for sphere and ray
// any point in ray: P = C + t*ray
// any point in sphere: |P−C|=r --> sqrt(P-C o P - C) = r --> (P-c)o(P-C) = r^2
t_inter	*find_sphere_inters(t_coord ray, t_scene *scene, t_sphere *sp)
{
	t_inter			*inter1;
	t_inter			*inter2;
	t_quadr_coef	qc;
	t_coord			cam_to_sp;
	t_camera cam = scene->c;

	inter1 = NULL;
	inter2 = NULL;
	cam_to_sp = make_vector(sp->centre, cam.point);
	qc.a = get_dot_product(ray, ray);
	qc.b = 2 * get_dot_product(cam_to_sp, ray);
	qc.c = get_dot_product(cam_to_sp, cam_to_sp) - pow((sp->diameter) / 2, 2);
	find_roots(&qc);
	if (qc.t1 > EPSILON)
	{
		inter1 = make_inter((void *)sp, qc.t1, ray, cam);
		set_id_colour_type(inter1, sp->id, SPHERE, sp->colour);
	}
	if (qc.t2 > EPSILON && qc.t2 != qc.t1)
	{
		inter2 = make_inter((void *)sp, qc.t2, ray, cam);
		set_id_colour_type(inter2, sp->id, SPHERE, sp->colour);
	}
	return (return_object_inters(inter1, inter2));
}
