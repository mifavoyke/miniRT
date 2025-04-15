/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpiarova <zpiarova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:22:46 by zpiarova          #+#    #+#             */
/*   Updated: 2025/04/15 11:19:28 by zpiarova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

// gets a scalar number from 2 vectors
// dot product of a vector with itself is its length
float get_dot_product(t_coord A, t_coord B)
{
    return (A.x * B.x + A.y * B.y + A.z * B.z);
}

// computes cross product of two normalized vectors
// results in a vector that is perpendicular to both vectors
t_coord get_cross_product(t_coord A, t_coord B)
{
    t_coord cross_product;
    
    cross_product.x = A.y * B.z - A.z * B.y;
    cross_product.y = A.z * B.x - A.x * B.z;
    cross_product.z = A.x * B.y - A.y * B.x;
    return (cross_product);
}

// normalized vector has a magnitude (length) of 1
// l = sqrt (x^2 + y^2 + z^2) = 1 --> must be true (deviation 0.002 accepted)
int is_vector_normalized(t_coord v)
{
    float   result;

    result = sqrt(pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2));
    return (result > 0.97 && result < 1.03);
}

// normalizes the vector so its length is 0
// N(normalized) = N / |N|
void normalize(t_coord *N)
{
    float len;
    
    len = sqrt(pow(N->x, 2) + pow(N->y, 2) + pow(N->z, 2));
    N->x = N->x / len;
    N->y = N->y / len;
    N->z = N->z / len;
}

// makes a vector from point A to point B
t_coord make_vector(t_coord from, t_coord to)
{
    t_coord vector;

    vector.x = to.x - from.x;
    vector.y = to.y - from.y;
    vector.z = to.z - from.z;
    return (vector);
}

// finds coordinate of another point P on vector v in distance d from point C
// P2 = P1 + d * v;
t_coord get_point_on_vector(t_coord C, t_coord v, float d)
{
    t_coord P;

    P.x = C.x + v.x * d;
    P.y = C.y + v.y * d;
    P.z = C.z + v.z * d;
    return (P);
}

// if  cross product of 2 vectors is (0,0,0), they are collinear
// @returns 1 if are collinear, 0 if not
bool are_collinear(t_coord A, t_coord B)
{
    t_coord cross_product;
    
    cross_product = get_cross_product(A, B);
    return (fabs(cross_product.x) < EPSILON && fabs(cross_product.y) < EPSILON && fabs(cross_product.z) < EPSILON);
}

// gets the difference between vectors
t_coord subtract_vectors(t_coord from, t_coord to)
{
    t_coord result_v;

    result_v.x = from.x - to.x;
    result_v.y = from.y - to.y;
    result_v.z = from.z - to.z;
    return (result_v);
}

// multiplies one vector with a constant
t_coord multiply_vector_by_constant(t_coord v, float n)
{
    t_coord result_v;

    result_v.x = v.x * n;
    result_v.y = v.y * n;
    result_v.z = v.z * n;
    return (result_v);
}
