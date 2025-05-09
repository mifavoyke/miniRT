/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_intersections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhusieva <yhusieva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 12:03:06 by zpiarova          #+#    #+#             */
/*   Updated: 2025/05/09 16:30:52 by yhusieva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minirt.h"

// sets attributes to inter pointer
// color, id and type have to be set outside of func BECAUSE OF FCKING NORMINET
void	set_id_colour_type(t_inter *inter, int id, enum e_obj_t t, t_colour c)
{
	inter->id = id;
	inter->colour = c;
	inter->type = t;
}

// allocates intersection node and fills it with required data
// color, id and type have to be set outside of func BECAUSE OF FCKING NORMINET
t_inter	*make_inter(void *obj, float t, t_coord ray, t_scene *scene)
{
	t_inter	*inter;
	t_camera cam = scene->c;

	inter = (t_inter *)malloc(sizeof(t_inter));
	if (!inter)
		return (NULL);
	inter->obj = obj;
	inter->distance = fabsf(t);
	inter->point = set_coord(
			cam.point.x + t * ray.x,
			cam.point.y + t * ray.y,
			cam.point.z + t * ray.z
			);
	inter->next = NULL;
	return (inter);
}

// returns intersection list for a specific object with one ray
t_inter	*return_object_inters(t_inter *in1, t_inter *in2)
{
	if (!in1 && !in2)
		return (NULL);
	if (in1)
	{
		append_node(in2, &in1);
		return (in1);
	}
	else if (in2)
		return (in2);
	return (NULL);
}
