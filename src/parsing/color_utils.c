/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zuzanapiarova <zuzanapiarova@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 10:05:20 by zuzanapiaro       #+#    #+#             */
/*   Updated: 2025/04/26 18:47:30 by zuzanapiaro      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	print_colour(t_colour colour)
{
	printf("(%d, %d, %d)", colour.r, colour.g, colour.b);
}

// sets colour in rgba format
t_colour	set_colour(int r, int b, int g, int a)
{
	t_colour	clr;

	clr.r = r;
	clr.b = b;
	clr.g = g;
	clr.a = a;
	return (clr);
}

t_colour	parse_colour(char *clr)
{
	t_colour	colour;
	char		**values;

	values = ft_split(clr, ',');
	if (!values || !values[0] || !values[1] || !values[2])
	{
		free_arr(values);
		printf("Error: Invalid colour format.\n");
		return (set_colour(-1, -1, -1, -1));
	}
	colour.r = ft_atoi(values[0]);
	colour.g = ft_atoi(values[1]);
	colour.b = ft_atoi(values[2]);
	colour.a = 255;
	free_arr(values);
	if (colour.r < 0 || colour.r > 255
		|| colour.g < 0 || colour.g > 255
		|| colour.b < 0 || colour.b > 255)
	{
		printf("Error: Colour values out of range.\n");
		return (set_colour(-1, -1, -1, -1));
	}
	return (colour);
}

int	invalid_colour(t_colour *clr)
{
	return (clr->r == -1 && clr->r == -1 && clr->r == -1);
}

// converts r, g, b values to hex
int32_t	ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
	int32_t	pixel;

	pixel = r << 24;
	pixel |= g << 16;
	pixel |= b << 8;
	pixel |= a;
	return (pixel);
}
