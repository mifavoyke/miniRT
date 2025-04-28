/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpiarova <zpiarova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 11:38:51 by zpiarova          #+#    #+#             */
/*   Updated: 2025/04/28 15:01:30 by zpiarova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

t_colour	**allocate_pixels(int width, int height, t_colour background_color)
{
	t_colour	**pixels;
	int			y;
	int			x;

	pixels = (t_colour **)malloc(height * sizeof(t_colour *));
	if (!pixels)
		return (NULL);
	y = -1;
	while (++y < height)
	{
		pixels[y] = (t_colour *)malloc(width * sizeof(t_colour));
		if (!pixels[y])
		{
			while (--y >= 0)
				free(pixels[y]);
			free(pixels);
			return (NULL);
		}
		x = -1;
		while (++x < width)
			pixels[y][x] = background_color;
	}
	return (pixels);
}

// allocates memory for 2D array of linked lists and sets each to NULL
t_inter	***allocate_inter(int width, int height)
{
	t_inter	***section;
	int		y;
	int		x;

	section = (t_inter ***)malloc(height * sizeof(t_inter **));
	if (!section)
		return (NULL);
	y = -1;
	while (++y < height)
	{
		section[y] = (t_inter **)malloc(width * sizeof(t_inter *));
		if (!section[y])
		{
			while (--y >= 0)
				free(section[y]);
			free(section);
			return (NULL);
		}
		x = -1;
		while (++x < width)
			section[y][x] = NULL;
	}
	return (section);
}
