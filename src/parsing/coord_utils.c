/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coord_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpiarova <zpiarova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 17:34:24 by zuzanapiaro       #+#    #+#             */
/*   Updated: 2025/04/29 11:08:18 by zpiarova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	print_coord(t_coord coord)
{
	printf("(%f, %f, %f)\n", coord.x, coord.y, coord.z);
}

// sets coordinate/vector
t_coord	set_coord(float x, float y, float z)
{
	t_coord	coord;

	coord.x = x;
	coord.y = y;
	coord.z = z;
	return (coord);
}

t_coord	parse_coord(char *coord)
{
	t_coord	parsed;
	char	**values;

	values = ft_split(coord, ',');
	if (!values || !values[0] || !values[1] || !values[2])
	{
		free_arr(values);
		printf("Error: Invalid coordinate format.\n");
		return (set_coord(INT_ERROR, INT_ERROR, INT_ERROR));
	}
	parsed.x = ft_atof(values[0]);
	parsed.y = ft_atof(values[1]);
	parsed.z = ft_atof(values[2]);
	free_arr(values);
	if (parsed.x == INT_MIN || parsed.y == INT_MIN || parsed.z == INT_MIN)
	{
		printf("Error: Coordinate out of allowed range.\n");
		return (set_coord(INT_ERROR, INT_ERROR, INT_ERROR));
	}
	return (parsed);
}

int	invalid_coord(t_coord *coord)
{
	return (coord->x == INT_ERROR
		&& coord->y == INT_ERROR
		&& coord->z == INT_ERROR);
}
