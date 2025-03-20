/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpiarova <zpiarova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 14:13:09 by zpiarova          #+#    #+#             */
/*   Updated: 2025/03/20 14:13:10 by zpiarova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

// Add diffuse lighting (light from a source hitting surfaces directly).
//  The reflection direction is calculated using the reflection formula,
//  which comes from the physics of mirror-like (specular) reflections.

// When light hits a surface, we have:
// 1. Incident vector (I): The direction from which the light comes.
// 2. Surface normal (N): The normal of the surface at the intersection point.
// 3. Reflected vector (R): The outgoing direction after reflection.

// For perfect mirrors, use the reflected ray direction to trace a new ray.
// For semi-reflective surfaces, blend the reflection with the object's base color using the Phong Reflection Model or Fresnel equations.
// For blurred reflections, slightly randomize R within a small cone to create a rough surface effect. - bonus?

// Reflected vector: R = I − 2*(I*N)*N
// int reflected_vector()
// {

// }
