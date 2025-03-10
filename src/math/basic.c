/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpiarova <zpiarova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:22:42 by zpiarova          #+#    #+#             */
/*   Updated: 2025/03/10 20:54:02 by zpiarova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

// self explanatory
// if D > 0 --> 2 roots (the ray enters and exits - 2 spots)
//    D = 0 --> 1 root (touches the surface)
//    D < 0 --> no roots (does not intersect)
float get_discriminant(float a, float b, float c)
{
    return (pow(b, 2) - 4 * a * c);
}

// linear interpolation function = maps/scales points proportionate and
// linearly to other points to keep the proportions but scaled in/out
double	scale(double num, double new_min, double new_max, double old_max)
{
	return ((new_max - new_min) * (num) / ((old_max)) + new_min);
}

// change coordinates top-left(TL) to center(C) system 
// TLx=ScreenWidth/2+Cx
// TLy=SceenHeight/2−Cy
int transform_to_tl(char coordinate, float value)
{
    if (coordinate == 'x')
        return (WIDTH / 2 + value);
    if (coordinate == 'y')
        return (HEIGHT / 2 - value);
    return (0);
}