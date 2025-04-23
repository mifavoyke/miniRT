/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_pixels.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhusieva <yhusieva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 14:13:28 by zpiarova          #+#    #+#             */
/*   Updated: 2025/04/23 19:46:30 by yhusieva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

// sets all pixels to the colour of the background by default
int init_pixels(t_minirt *minirt)
{
	int x;
	int y;

	minirt->pixels = allocate_pixels(minirt->img_width, minirt->img_height);
	if (!minirt->pixels)
		return (ERROR);
	y = -1;
	while (++y < minirt->img_height)
	{
		x = -1;
		while (++x < minirt->img_width)
			minirt->pixels[y][x] = minirt->scene->background;
	}
	return (0);
}
