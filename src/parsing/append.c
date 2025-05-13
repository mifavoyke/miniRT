/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zuzanapiarova <zuzanapiarova@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 12:06:17 by zuzanapiaro       #+#    #+#             */
/*   Updated: 2025/05/13 12:06:18 by zuzanapiaro      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

// appends new allocated light sources to the list
void	append_light(t_light **l_list, t_light *new_l)
{
	t_light	*tmp;

	if (!l_list || !*l_list)
		*l_list = new_l;
	else
	{
		tmp = *l_list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_l;
	}
}

// appends new allocated sphere instance to the sphere list
void	append_sphere(t_sphere **sphere_list, t_sphere *new_sphere)
{
	t_sphere	*tmp;

	if (!sphere_list || !*sphere_list)
		*sphere_list = new_sphere;
	else
	{
		tmp = *sphere_list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_sphere;
	}
}

// appends new allocated plane instance to the plane list
void	append_plane(t_plane **plane_list, t_plane *new_plane)
{
	t_plane	*tmp;

	if (!plane_list || !*plane_list)
		*plane_list = new_plane;
	else
	{
		tmp = *plane_list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_plane;
	}
}

// appends new allocated cylinder instance to the sphere list
void	append_cylinder(t_cylinder **cylinder_list, t_cylinder *new_cyl)
{
	t_cylinder	*tmp;

	if (!cylinder_list || !*cylinder_list)
		*cylinder_list = new_cyl;
	else
	{
		tmp = *cylinder_list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_cyl;
	}
}
