/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpiarova <zpiarova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:22:42 by zpiarova          #+#    #+#             */
/*   Updated: 2025/03/12 12:22:46 by zpiarova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

// checks if two floats are equal accepting a set deviation
int equals(float a, float b, float deviation)
{
    return (fabs(a - b) <= deviation);
}

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
// would also need old_min but bcs of norminette use only when it is 0
double	scale(double num, double new_min, double new_max, double old_max)
{
	return ((new_max - new_min) * (num) / ((old_max)) + new_min);
}