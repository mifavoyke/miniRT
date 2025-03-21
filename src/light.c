/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpiarova <zpiarova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 14:13:09 by zpiarova          #+#    #+#             */
/*   Updated: 2025/03/21 14:57:25 by zpiarova         ###   ########.fr       */
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

t_coord reflected_vector(t_light *light, t_inter *section) // BRDF
{
    t_sphere *sp;
    t_coord normal;     // normal of the sphere which is always the vector from the centre of the sphere to the intersection point
    t_coord incident_l; // incident light vector
    t_coord reflected;
    float scalar;

    sp = (t_sphere *)section->obj;
    // REFLECTION RAY R = I − 2*(I*N)*N
    // 1.1 find incident light vector
    incident_l = make_vector(light->lightpoint, section->point);
    normalize(&incident_l);
    // 1.2 compute the normal at the intersection
    normal = make_vector(sp->centre, section->point);
    normalize(&normal);
    // 1.3 find the scalar from I and N
    scalar = get_dot_product(incident_l, normal);
    // 1.4 FINAL substitute into the formula for the reflected vector
    // reflected = I - 2 * cosine_IN * N;
    reflected = subtract_vectors(incident_l, multiply_vector(normal, 2 * scalar));
    printf("\nReflected vector is: R(%f, %f, %f)\n", reflected.x, reflected.y, reflected.z);
    // if this reflected ray hits another obj, repeat the process ???
    return (reflected);
}

float specular_light(t_camera *cam, t_light *light, t_inter *section, t_coord reflected) // Phong reflection model
{
    float cosine_reflected_viewpoint;
    t_coord incident_c; // incident vector from the camera
    float specular_intensity;

    // find V = C - P = camera position - intersection point
    incident_c = make_vector(cam->point, section->point);
    normalize(&incident_c);
    // PHONG FORMULA Iv = k(R*V)pow(a)
    cosine_reflected_viewpoint = get_dot_product(reflected, incident_c);
    specular_intensity = light->brightness * pow(cosine_reflected_viewpoint, 20);
    printf("Interim result before power: %f and after: %f\n", cosine_reflected_viewpoint, pow(cosine_reflected_viewpoint, 20));
    printf("Specular light: %f\n", specular_intensity);
    return (specular_intensity);
}

t_colour apply_light(t_colour original, t_colour light, float reflectivity)
{
    t_colour final_color;

    final_color.r = original.r * (1 - reflectivity) + light.r * reflectivity;
    final_color.g = original.g * (1 - reflectivity) + light.g * reflectivity;
    final_color.b = original.b * (1 - reflectivity) + light.b * reflectivity;
    final_color.a = 255;
    printf("Colour after the light (%d, %d, %d)\n", final_color.r, final_color.g, final_color.b);
    return (final_color);
}

int lighting(t_minirt *minirt)
{
    t_coord reflected;
    float specular_intensity;
    int y;
    int x;

    y = -1;
    while (++y < minirt->img_height)
    {
        x = -1;
        while (++x < minirt->img_width)
        {
            reflected = reflected_vector(&minirt->scene->l, minirt->intersection[y][x]);
            specular_intensity = specular_light(&minirt->scene->c, &minirt->scene->l, minirt->intersection[y][x], reflected);
            if (minirt->intersection[y][x])
                minirt->pixels[y][x] = apply_light(minirt->intersection[y][x]->colour, minirt->scene->l.colour, specular_intensity);
        }
    }
    return (0);
}