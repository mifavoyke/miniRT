/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhusieva <yhusieva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 17:03:09 by zpiarova          #+#    #+#             */
/*   Updated: 2025/03/20 13:58:21 by yhusieva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void render_pixels(t_minirt *minirt)
{
	int x;
    int y;
    t_colour c;

	y = -1;
	while (++y < minirt->img_height)
	{
		x = -1;
		while (++x < minirt->img_width)
		{
			c = minirt->pixels[y][x];
			mlx_put_pixel(minirt->img, x, y, ft_pixel(c.r, c.g, c.b, c.a));
		}
	}
}
