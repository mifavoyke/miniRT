/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_intersections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zuzanapiarova <zuzanapiarova@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 12:03:06 by zpiarova          #+#    #+#             */
/*   Updated: 2025/05/14 08:55:55 by zuzanapiaro      ###   ########.fr       */
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
t_inter	*make_inter(void *obj, float t, t_coord ray, t_coord origin)
{
	t_inter	*inter;

	inter = (t_inter *)malloc(sizeof(t_inter));
	if (!inter)
		return (NULL);
	inter->obj = obj;
	inter->distance = fabsf(t);
	inter->point = set_coord(
			origin.x + t * ray.x,
			origin.y + t * ray.y,
			origin.z + t * ray.z
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

void	set_cyl_roots(t_roots *roots, float t1, float t2, enum e_obj_t type)
{
	if (t2 != t1)
	{
		if (roots->t1 != -1)
		{
			roots->t2 = t2;
			roots->type2 = type;
		}
		else
		{
			roots->t1 = t2;
			roots->type1 = type;
		}
	}
}

void	final_cyl_roots(t_roots *roots, t_roots new_roots)
{
	if (roots->t1 == -1)
	{
		roots->t1 = new_roots.t1;
		roots->type1 = new_roots.type1;
		roots->t2 = new_roots.t2;
		roots->type2 = new_roots.type2;
	}
	else
	{
		roots->t2 = new_roots.t1;
		roots->type2 = new_roots.type1;
	}
}
