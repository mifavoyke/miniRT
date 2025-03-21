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

t_coord reflected_vector(t_light_components *l_component, t_light *light, t_inter *section) // BRDF
{
    t_sphere *sp;
    t_coord normal;     // normal of the sphere which is always the vector from the centre of the sphere to the intersection point
    t_coord incident_l; // incident light vector
    t_coord reflected;

    sp = (t_sphere *)section->obj;
    // REFLECTION RAY R = I − 2*(I*N)*N
    // 1.1 find incident light vector
    incident_l = make_vector(light->lightpoint, section->point);
    normalize(&incident_l);
    // 1.2 compute the normal at the intersection
    normal = make_vector(sp->centre, section->point);
    normalize(&normal);
    // 1.3 find the scalar from I and N
    l_component->scalar_normal_light = get_dot_product(incident_l, normal);
    // 1.4 FINAL substitute into the formula for the reflected vector
    // reflected = I - 2 * cosine_IN * N;
    reflected = subtract_vectors(incident_l, multiply_vector(normal, 2 * l_component->scalar_normal_light));
    // printf("\nReflected vector is: R(%f, %f, %f)\n", reflected.x, reflected.y, reflected.z);
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
    specular_intensity = light->brightness * pow(fmax(0, cosine_reflected_viewpoint), GLASS);
    // printf("Interim result (the cosine) before power: %f\nand after: %f\nresult: %f\n", cosine_reflected_viewpoint, pow(fmax(0, cosine_reflected_viewpoint), GLASS), specular_intensity);
    return (specular_intensity);
}

t_colour apply_light(t_colour original, t_colour light, float reflectivity)
{
    t_colour final_color;

    final_color.r = fmax(0, fmin(255, original.r * (1 - reflectivity) + light.r * reflectivity));
    final_color.g = fmax(0, fmin(255, original.g * (1 - reflectivity) + light.g * reflectivity));
    final_color.b = fmax(0, fmin(255, original.b * (1 - reflectivity) + light.b * reflectivity));
    final_color.a = 255;
    // printf("Colour after the light (%d, %d, %d)\n", final_color.r, final_color.g, final_color.b);
    return (final_color);
}

// Lambertian reflectance Id = k*(N*L)
float diffuse_ambient_light(float scalar_nl, float light_ratio, float ambient)
{
    float final_lighting;

    final_lighting = 0;
    if (scalar_nl > 0)
        final_lighting = light_ratio * scalar_nl;
    final_lighting += ambient;
    return (final_lighting);
}

int lighting(t_minirt *minirt)
{
    t_coord reflected;
    float reflectivity;
    t_light_components l_components;
    int y;
    int x;

    y = -1;
    while (++y < minirt->img_height)
    {
        x = -1;
        while (++x < minirt->img_width)
        {
            if (minirt->intersection[y][x])
            {
                reflected = reflected_vector(&l_components, &minirt->scene->l, minirt->intersection[y][x]);
                reflectivity = specular_light(&minirt->scene->c, &minirt->scene->l, minirt->intersection[y][x], reflected);
                reflectivity += diffuse_ambient_light(l_components.scalar_normal_light, minirt->scene->l.brightness, minirt->scene->a.ratio);
                minirt->pixels[y][x] = apply_light(minirt->intersection[y][x]->colour, minirt->scene->l.colour, reflectivity);
            }
            // else
            // {
            //     ? ? ?
            // }
        }
    }
    return (0);
}
