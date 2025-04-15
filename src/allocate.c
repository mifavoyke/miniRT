/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpiarova <zpiarova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 11:38:51 by zpiarova          #+#    #+#             */
/*   Updated: 2025/04/15 11:39:37 by zpiarova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

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

// WE DO NOT NEED THIS IF WE CHECK FOR LIGHT IN THE SHOOT_RAY FUNCTION - OR ? -Z.
t_inter ***allocate_inter(int width, int height)
{
	t_inter ***section;
	int y;

	section = (t_inter ***)malloc(height * sizeof(t_inter **));
	if (!section)
		return (NULL);
	y = -1;
	while (++y < height)
	{
		section[y] = (t_inter **)malloc(width * sizeof(t_inter *));
		if (!section[y])
			return (NULL);
	}
	return (section);
}
