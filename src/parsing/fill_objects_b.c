/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_objects_b.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zuzanapiarova <zuzanapiarova@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 17:45:17 by zuzanapiaro       #+#    #+#             */
/*   Updated: 2025/04/26 18:15:29 by zuzanapiaro      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

// appends new allocated cylinder instance to the sphere list
void	append_cylinder(t_cylinder **cylinder_list, t_cylinder *new_cylinder)
{
	t_cylinder	*tmp;

	if (!cylinder_list || !*cylinder_list)
		*cylinder_list = new_cylinder;
	else
	{
		tmp = *cylinder_list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_cylinder;
	}
}

// checks possible error values for cylinder and writes respective message
// returns 1 if any value is wrong, 0 if all are OK
int	check_error_values_cylinder(t_cylinder *cylinder)
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
int	fill_cylinder(t_scene *scene, char **values, int i)
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
	new_cyl->id = i - 1;
	new_cyl->next = NULL;
	append_cylinder(&(scene->cy), new_cyl);
	scene->cy_count++;
	return (0);
}
