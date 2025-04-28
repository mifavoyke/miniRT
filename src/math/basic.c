/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zuzanapiarova <zuzanapiarova@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:22:42 by zpiarova          #+#    #+#             */
/*   Updated: 2025/04/26 19:55:15 by zuzanapiaro      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

// checks if two floats are equal accepting a set deviation
int	equals(float a, float b, float deviation)
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

// calculates width of the viewport plane (representing screen) in the 3d space
// radians re used for calculation in functions !
float get_viewport_width(float angle_deg, float distance)
{
	float   viewport_width;
	float   angle_rad;

	angle_rad = angle_deg * M_PI / 180.0;
	viewport_width = 2 * (tan(angle_rad / 2) * distance);  
	return (viewport_width);
}

// calculates height of the viewport plane (representing screen) based on viewport width
// keeps the width:height ratio of screen 
float get_viewport_height(float viewport_width)
{
	return (viewport_width * HEIGHT / WIDTH);
}