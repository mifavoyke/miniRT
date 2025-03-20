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

// I - the vector from the camera to an intersection with an object

// typedef struct s_light
// {
//     t_coord lightpoint;
//     float brightness;
//     t_colour colour; // bonus
// } t_light;

// C   -5,35,50	0,0,-1.0	70
// L   10,10,10				0.5	255,255,0

t_coord subtract_vectors(t_coord from, t_coord to)
{
    t_coord result_v;

    result_v.x = from.x - to.x;
    result_v.y = from.y - to.y;
    result_v.z = from.z - to.z;
    return (result_v);
}

t_coord multiply_vector(t_coord v, float n)
{
    t_coord result_v;

    result_v.x = v.x * n;
    result_v.y = v.y * n;
    result_v.z = v.z * n;
    return (result_v);
}

t_coord reflected_vector() // BRDF
{
    t_coord P_intersection = {5, 20, 30};
    t_coord O_sp_centre = {0, 15, 30}; // for N
    t_coord L = {10, 10, 10};
    t_coord N; // normal of the sphere which is always the vector from the centre of the sphere to the intersection point
    t_coord I; // incident light vector
    t_coord R_eflected;
    float cosine_IN;

    // REFLECTION RAY R = I − 2*(I*N)*N
    // 1.1 find incident light vector
    I = make_vector(L, P_intersection);
    normalize(&I);
    // 1.2 compute the normal at the intersection
    N = make_vector(O_sp_centre, P_intersection);
    normalize(&N);
    // 1.3 find the scalar from I and N
    cosine_IN = get_dot_product(I, N);
    // 1.4 FINAL substitute into the formula for the reflected vector
    // R_eflected = I - 2 * cosine_IN * N;
    R_eflected = subtract_vectors(I, multiply_vector(N, 2 * cosine_IN));
    printf("\nReflected vector is: R(%f, %f, %f)\n", R_eflected.x, R_eflected.y, R_eflected.z);
    // if this reflected ray hits another obj, repeat the process ???
    phong_reflection_model();
    apply_light();
    return (R_eflected);
}

float phong_reflection_model()
{
    t_coord C = {-5, 35, 50}; // camera position
    t_coord P_intersection = {5, 20, 30};
    float brightness_ratio = 0.8;
    t_coord R = {-0.436436, 0.218218, 0.872872};
    float scalar_RV;
    t_coord V; // incident vector from the camera
    float specular_intensity;

    // find V
    V = make_vector(C, P_intersection);
    normalize(&V);
    // PHONG FORMULA Iv = k(R*V)pow(a)
    scalar_RV = get_dot_product(R, V);
    specular_intensity = brightness_ratio * pow(scalar_RV, 20);
    printf("Interim result before power: %f and after: %f\n", scalar_RV, pow(scalar_RV, 20));
    printf("Specular light: %f\n", specular_intensity);
    return (specular_intensity);
}

t_colour apply_light()
{
    float reflectivity = 0.195649;
    t_colour orig_c = {50, 50, 255, 255};
    t_colour light_c = {255, 255, 255, 255};
    t_colour final_c;

    final_c.r = orig_c.r * (1 - reflectivity) + light_c.r * reflectivity;
    final_c.g = orig_c.g * (1 - reflectivity) + light_c.g * reflectivity;
    final_c.b = orig_c.b * (1 - reflectivity) + light_c.b * reflectivity;
    final_c.a = 255;
    printf("Colour after the light (%d, %d, %d)\n", final_c.r, final_c.g, final_c.b);
    return (final_c);
}
