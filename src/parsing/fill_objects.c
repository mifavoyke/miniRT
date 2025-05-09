/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_objects_a.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhusieva <yhusieva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 18:27:16 by zuzanapiaro       #+#    #+#             */
/*   Updated: 2025/05/09 16:48:38 by yhusieva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

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
	return (SUCCESS);
}

// checks possible error values for cylinder and writes respective message
// returns 1 if any value is wrong, 0 if all are OK
static int	check_error_values_cylinder(t_cylinder *cylinder)
{
	if (invalid_coord(&cylinder->centre))
		return (ERROR);
	else if (invalid_colour(&cylinder->colour))
		return (ERROR);
	else if (!cylinder->vector.x && !cylinder->vector.y && !cylinder->vector.z)
		return (ft_error("Cylinder orientation vector can't be (0,0,0)."));
	else if (cylinder->diameter <= 0)
		return (ft_error("Cylinder diameter must be greater than zero."));
	else if (cylinder->height <= 0)
		return (ft_error("Cylinder height must be greater than zero."));
	else
		return (SUCCESS);
}

// fills cylinder object from array of values from one row with identifier cy
// if any exist before, appends new sphere node after the existing ones
// expects cy  POINT[x,y,z]  diameter(0-180˚)  colour(r,g,b)
int	fill_cylinder(t_scene *scene, char **values, int *i)
{
	t_cylinder	*new_cyl;

	if (!values[1] || !values[2] || !values[3] || !values[4]
		|| !values[5] || values[6])
		return (ft_error("Cylinder missing/extra parameters."));
	new_cyl = malloc(sizeof(t_cylinder));
	if (!new_cyl)
		return (ft_error("Memory allocation failed for cylinder."));
	new_cyl->centre = parse_coord(values[1]);
	new_cyl->vector = parse_coord(values[2]);
	if (!is_vector_normalized(new_cyl->vector))
		normalize(&new_cyl->vector);
	new_cyl->diameter = ft_atof(values[3]);
	new_cyl->height = ft_atof(values[4]);
	new_cyl->colour = parse_colour(values[5]);
	if (check_error_values_cylinder(new_cyl) == ERROR)
	{
		free(new_cyl);
		return (ERROR);
	}
	new_cyl->id = (*i)++;
	new_cyl->next = NULL;
	append_cylinder(&(scene->cy), new_cyl);
	return (0);
}
