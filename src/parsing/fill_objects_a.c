/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_objects_a.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpiarova <zpiarova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 18:27:16 by zuzanapiaro       #+#    #+#             */
/*   Updated: 2025/05/09 10:59:05 by zpiarova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

// appends new allocated sphere instance to the sphere list
static void	append_sphere(t_sphere **sphere_list, t_sphere *new_sphere)
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
static void	append_plane(t_plane **plane_list, t_plane *new_plane)
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

// fills the sphere object from array of values from one row with identifier sp
// if any exist before, appends new sphere node after the existing ones
// expects sp  POINT[x,y,z]  diameter(0-180˚)  colour(r,g,b)
int	fill_sphere(t_scene *scene, char **values, int *i)
{
	t_sphere	*new_sphere;

	if (!values[1] || !values[2] || !values[3] || values[4])
		return (ft_error("Sphere missing/extra parameters."));
	new_sphere = malloc(sizeof(t_sphere));
	if (!new_sphere)
		return (ft_error("Memory allocation failed for sphere."));
	new_sphere->centre = parse_coord(values[1]);
	new_sphere->diameter = ft_atof(values[2]);
	new_sphere->colour = parse_colour(values[3]);
	if (invalid_coord(&new_sphere->centre)
		|| new_sphere->diameter <= 0
		|| invalid_colour(&new_sphere->colour))
	{
		if (new_sphere->diameter <= 0)
			ft_error("Sphere diameter must be greater than zero.");
		free(new_sphere);
		return (ERROR);
	}
	new_sphere->id = *i;
	(*i)++;
	new_sphere->next = NULL;
	append_sphere(&(scene->sp), new_sphere);
	scene->sp_count++;
	return (SUCCESS);
}

// fills the plane object from array of values from one row with identifier pl
// if any exist before, appends new sphere node after the existing ones
// expects pl  POINT[x,y,z]  normal_vector(x,y,z)  colour(r,g,b)
int	fill_plane(t_scene *scene, char **values, int *i)
{
	t_plane	*new_pl;

	if (!values[1] || !values[2] || !values[3] || values[4])
		return (ft_error("Plane missing/extra parameters."));
	new_pl = malloc(sizeof(t_plane));
	if (!new_pl)
		return (ft_error("Memory allocation failed for plane."));
	new_pl->point = parse_coord(values[1]);
	new_pl->vector = parse_coord(values[2]);
	if (!is_vector_normalized(new_pl->vector))
		normalize(&new_pl->vector);
	new_pl->colour = parse_colour(values[3]);
	if (invalid_coord(&new_pl->point) || invalid_colour(&new_pl->colour)
		|| (!new_pl->vector.x && !new_pl->vector.y && !new_pl->vector.z))
	{
		if (!new_pl->vector.x && !new_pl->vector.y && !new_pl->vector.z)
			ft_error("Plane normal vector cannot be (0,0,0).");
		free(new_pl);
		return (ERROR);
	}
	new_pl->id = (*i)++;
	new_pl->next = NULL;
	append_plane(&(scene->pl), new_pl);
	scene->pl_count++;
	return (SUCCESS);
}
