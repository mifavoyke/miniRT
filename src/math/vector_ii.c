/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_ii.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpiarova <zpiarova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 13:28:02 by zpiarova          #+#    #+#             */
/*   Updated: 2025/05/01 15:14:16 by zpiarova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

// finds coordinate of another point P on vector v in distance d from point C
// P2 = P1 + d * v;
t_coord	get_point_on_vector(t_coord C, t_coord v, float d)
{
	t_coord	p;

	p.x = C.x + v.x * d;
	p.y = C.y + v.y * d;
	p.z = C.z + v.z * d;
	return (p);
}

// if  cross product of 2 vectors is (0,0,0), they are collinear
// collinear means that 3 or more points of one line lay on the other line
// @returns 1 if are collinear, 0 if not
bool	are_collinear(t_coord A, t_coord B)
{
	t_coord	cross_product;

	cross_product = get_cross_product(A, B);
	return (fabs(cross_product.x) < EPSILON
		&& fabs(cross_product.y) < EPSILON
		&& fabs(cross_product.z) < EPSILON);
}

// gets the difference between vectors
t_coord	subtract_vectors(t_coord from, t_coord to)
{
	t_coord	result_v;

	result_v.x = from.x - to.x;
	result_v.y = from.y - to.y;
	result_v.z = from.z - to.z;
	return (result_v);
}

// multiplies one vector with a constant
t_coord	multiply_vector_by_constant(t_coord v, float n)
{
	t_coord	result_v;

	result_v.x = v.x * n;
	result_v.y = v.y * n;
	result_v.z = v.z * n;
	return (result_v);
}

// moves the point in the direction and size of the vector 
t_coord	move_point_by_vector(t_coord point, t_coord vector)
{
	t_coord	moved_point;

	moved_point.x = point.x + vector.x;
	moved_point.y = point.y + vector.y;
	moved_point.z = point.z + vector.z;
	return (moved_point);
}
