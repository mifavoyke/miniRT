/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_pixels.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhusieva <yhusieva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 14:13:28 by zpiarova          #+#    #+#             */
/*   Updated: 2025/03/21 15:49:39 by yhusieva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

t_colour **allocate_pixels(int width, int height)
{
	t_colour **pixels;
	int y;

	pixels = (t_colour **)malloc(height * sizeof(t_colour *));
	if (!pixels)
		return (NULL);
	y = -1;
	while (++y < height)
	{
		pixels[y] = (t_colour *)malloc(width * sizeof(t_colour));
		if (!pixels[y])
			return (NULL);
	}
	return (pixels);
}

void init_pixels(t_minirt *minirt)
{
	int x;
	int y;

	y = -1;
	while (++y < minirt->img_height)
	{
		x = -1;
		while (++x < minirt->img_width)
		{
			minirt->pixels[y][x] = minirt->scene->background;
		}
	}
}
