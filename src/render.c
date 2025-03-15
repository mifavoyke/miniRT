/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhusieva <yhusieva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 17:03:09 by zpiarova          #+#    #+#             */
/*   Updated: 2025/03/15 15:09:53 by yhusieva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void render_pixels(t_minirt *minirt)
{
	int x;
    int y;
    t_colour c;

	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
		{
			c = minirt->pixels[y][x].cl;
			mlx_put_pixel(minirt->img, x, y, ft_pixel(c.r, c.g, c.b, c.a));
		}
	}
}
