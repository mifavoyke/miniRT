/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_iii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpiarova <zpiarova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 13:33:59 by zpiarova          #+#    #+#             */
/*   Updated: 2025/05/09 11:23:22 by zpiarova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

// checks if two vectors are parallel - their cross product is 0
// @returns 1 if are parallel, 0 if not 
int	are_parallel(t_coord vector1, t_coord vector2)
{
	t_coord	cross;

	cross = get_cross_product(vector1, vector2);
	if (fabsf(cross.x) < EPSILON
		&& fabsf(cross.y) < EPSILON
		&& fabsf(cross.z) < EPSILON)
		return (1);
	return (0);
}

// multiply vector by the transpose of matrix R
// transpose of matrix R is matrix where rows become columns and vice versa
// it means dotting v with each row of R (which are columns in original matrix)
t_coord	multiply_transpose(t_matrix R, t_coord v)
{
	t_coord	result;
	result.x = v.x * R.right.x + v.y * R.forward.x + v.z * R.up.x;
	result.y = v.x * R.right.y + v.y * R.forward.y + v.z * R.up.y;
	result.z = v.x * R.right.z + v.y * R.forward.z + v.z * R.up.z;
	return (result);
}

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
