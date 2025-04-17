/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zuzanapiarova <zuzanapiarova@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 14:11:47 by zpiarova          #+#    #+#             */
/*   Updated: 2025/04/17 21:55:07 by zuzanapiaro      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

t_coord set_coord(float x, float y, float z)
{
	t_coord coord;

	coord.x = x;
	coord.y = y;
	coord.z = z;
	return (coord);
}

t_colour set_colour(int r, int b, int g, int a)
{
	t_colour clr;

	clr.r = r;
	clr.b = b;
	clr.g = g;
	clr.a = a;
	return (clr);
}

t_coord parse_coord(char *coord)
{
	t_coord parsed;
	char **values;

	values = ft_split(coord, ',');
	if (!values || !values[0] || !values[1] || !values[2])
	{
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

t_colour parse_colour(char *clr)
{
	t_colour colour;
	char **values;

	values = ft_split(clr, ',');
	if (!values || !values[0] || !values[1] || !values[2])
	{
		printf("Error: Invalid colour format.\n");
		return (set_colour(-1, -1, -1, -1));
	}
	colour.r = ft_atoi(values[0]);
	colour.g = ft_atoi(values[1]);
	colour.b = ft_atoi(values[2]);
	colour.a = 255;
	free_arr(values);
	if (colour.r < 0 || colour.r > 255 || colour.g < 0 || colour.g > 255 || colour.b < 0 || colour.b > 255)
	{
		printf("Error: Colour values out of range.\n");
		return (set_colour(-1, -1, -1, -1));
	}
	return (colour);
}

// counts all rows of the file
int	count_rows(char *arg)
{
	int		i;
	int		fd;
	char	*one_line;

	i = 0;
	fd = open(arg, O_RDONLY);
	if (fd == -1)
		return (0);
	one_line = get_next_line(fd);
	if (!one_line)
	{
		close(fd);
		return (0);
	}
	while (one_line)
	{
		i++;
		free(one_line);
		one_line = get_next_line(fd);
	}
	close(fd);
	return (i);
}

// stores lines from the .rt file in an array
// @returns array of lines from the file
char	**get_lines(char *arg, int size)
{
	char	**read_lines;
	char	*one_line;
	int		i;
	int		fd;

	i = 0;
	// read_lines = NULL;
	fd = open(arg, O_RDONLY);
	if (fd == -1)
		return (NULL);
	one_line = get_next_line(fd);
	if (!one_line)
	{
		close(fd);
		return (NULL);
	}
	read_lines = (char **)malloc(size * sizeof(char *));
	if (!read_lines)
	{
		close(fd);
		free(one_line);
		return (NULL);
	}
	while (one_line)
	{
		read_lines[i] = one_line;
		one_line = get_next_line(fd);
		i++;
	}
	free(one_line);
	close(fd);
	return (read_lines);
}
