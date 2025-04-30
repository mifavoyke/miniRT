/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_i.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpiarova <zpiarova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:22:46 by zpiarova          #+#    #+#             */
/*   Updated: 2025/04/30 13:38:42 by zpiarova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

// dot product is used to project one vector onto another
// gets scalar number from 2 vectors
// dot product of vector with itself is its length
float	get_dot_product(t_coord A, t_coord B)
{
	return (A.x * B.x + A.y * B.y + A.z * B.z);
}

// computes cross product of two normalized vectors
// results in a vector that is perpendicular to both vectors
t_coord	get_cross_product(t_coord A, t_coord B)
{
	t_coord	cross_product;

	cross_product.x = A.y * B.z - A.z * B.y;
	cross_product.y = A.z * B.x - A.x * B.z;
	cross_product.z = A.x * B.y - A.y * B.x;
	return (cross_product);
}

// normalized vector has a magnitude (length) of 1
// l = sqrt (x^2 + y^2 + z^2) = 1 --> must be true (deviation 0.002 accepted)
int	is_vector_normalized(t_coord v)
{
	float	result;

	result = sqrt(pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2));
	return (result > 0.97 && result < 1.03);
}

// normalizes the vector so its length is 0
// N(normalized) = N / |N|
void	normalize(t_coord *N)
{
	float	len;

	len = sqrt(pow(N->x, 2) + pow(N->y, 2) + pow(N->z, 2));
	if (len == 0)
	{
		N->x = 0;
		N->y = 0;
		N->z = 0;
	}
	else
	{
		N->x = N->x / len;
		N->y = N->y / len;
		N->z = N->z / len;
	}
}

// makes a vector from point A to point B
t_coord	make_vector(t_coord from, t_coord to)
{
	t_coord	vector;

	vector.x = to.x - from.x;
	vector.y = to.y - from.y;
	vector.z = to.z - from.z;
	return (vector);
}
