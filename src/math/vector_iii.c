/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_iii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpiarova <zpiarova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 13:33:59 by zpiarova          #+#    #+#             */
/*   Updated: 2025/04/30 13:38:08 by zpiarova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

// adds 2 vectors - x1+x2, y1+y2, z1+z2
t_coord	add_vectors(t_coord v1, t_coord v2)
{
	t_coord	new_v;

	new_v.x = v1.x + v2.x;
	new_v.y = v1.y + v2.y;
	new_v.z = v1.z + v2.z;
	return (new_v);
}

// rotates vector around axis by angle in radians using Rodriguez's formula
// WE USE LEFT-HANDED SYSTEM - F vector is minus cross product of RxU
// so the sinus component is set to minus: -sinf(angle) 
t_coord	rotate_vector_around_axis(t_coord v, t_coord axis, float angle)
{
	t_coord	result;
	float	c;
	float	s;

	c = cosf(angle);
	s = -sinf(angle);
	normalize(&axis);
	result.x = v.x * c
		+ (1 - c) * (axis.x * (axis.x * v.x + axis.y * v.y + axis.z * v.z))
		+ s * (axis.y * v.z - axis.z * v.y);
	result.y = v.y * c
		+ (1 - c) * (axis.y * (axis.x * v.x + axis.y * v.y + axis.z * v.z))
		+ s * (axis.z * v.x - axis.x * v.z);
	result.z = v.z * c
		+ (1 - c) * (axis.z * (axis.x * v.x + axis.y * v.y + axis.z * v.z))
		+ s * (axis.x * v.y - axis.y * v.x);
	return (result);
}
