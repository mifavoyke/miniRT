/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhusieva <yhusieva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 14:13:09 by zpiarova          #+#    #+#             */
/*   Updated: 2025/04/21 17:15:47 by yhusieva         ###   ########.fr       */
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

// mesh objects?

// calculates the closest point on the cylinder axis and finds the vector from
// that closest point on the axis to the intersection point
t_coord calculate_cylider_normal(t_cylinder *cy, t_coord intersection_p)
{
    t_coord closest_axis_point;
    t_coord normal;
    int t;

    t = get_dot_product(make_vector(cy->centre, intersection_p), cy->vector);
    closest_axis_point = get_point_on_vector(cy->centre, cy->vector, t);
    normal = make_vector(closest_axis_point, intersection_p);
    return (normal);
}

void init_inputs(t_inter *intersection, t_light_math *vars, t_coord lightpoint, t_coord viewpoint)
{
    t_sphere *sp;
    t_plane *pl;
    t_cylinder *cy;
    t_coord offset;

    if (intersection->type == SPHERE)
    {
        sp = (t_sphere *)intersection->obj;
        vars->normal = make_vector(sp->centre, intersection->point); // normal of the sphere which is always the vector from the centre of the sphere to the intersection point
    }
    else if (intersection->type == PLANE)
    {
        pl = (t_plane *)intersection->obj;
        vars->normal = set_coord(pl->vector.x, pl->vector.y, pl->vector.z);
    }
    else if (intersection->type == CYLINDER)
    {
        cy = (t_cylinder *)intersection->obj;
        if (cy->vector.z == 1 || cy->vector.z == -1)
            vars->normal = make_vector(cy->centre, intersection->point);
        else
            vars->normal = calculate_cylider_normal(cy, intersection->point);
    }
    normalize(&vars->normal);

    vars->shadow_ray = make_vector(intersection->point, lightpoint);
    vars->max_length = sqrtf(get_dot_product(vars->shadow_ray, vars->shadow_ray));
    normalize(&vars->shadow_ray);
    offset = multiply_vector_by_constant(vars->shadow_ray, 1);
    // printf("shadow ray:\n");
    // print_coord(vars->shadow_ray);
    vars->shadow_origin = move_point_by_vector(intersection->point, offset);
    // printf("coord of the intersection point, offset and the final shadow origin: \n");
    // print_coord(intersection->point);
    // print_coord(offset);
    // print_coord(vars->shadow_origin);

    vars->incident_l = make_vector(intersection->point, lightpoint);
    normalize(&vars->incident_l);
    vars->scalar_nl = get_dot_product(vars->incident_l, vars->normal);
    
    vars->incident_v = make_vector(viewpoint, intersection->point);
    normalize(&vars->incident_v);
    vars->reflectivity = 0.0;
}

// bidirectional reflectance distribution function (BRDF)
// reflected vector: R = I − 2*N *(I*N)
t_coord reflected_vector(t_light_math *inputs)
{
    t_coord scaled_normal_vector;

    scaled_normal_vector = multiply_vector_by_constant(inputs->normal, 2 * inputs->scalar_nl);
    inputs->reflected_vector = subtract_vectors(inputs->incident_l, scaled_normal_vector);
    return (inputs->reflected_vector);
}

// Phong reflection model for specular light: Is = max{0, k * (R*V)^n}
float specular_light(t_light_math *inputs, float light_brightness) // Phong reflection model
{
    inputs->scalar_vr = get_dot_product(inputs->reflected_vector, inputs->incident_v);
    inputs->reflectivity = fmax(0, (light_brightness * pow(inputs->scalar_vr, PLASTIC)));
    return (inputs->reflectivity);
}

// Lambertian reflectance for diffuse light: Id = max{0, k * (N*L)}
float diffuse_light(float scalar_nl, float light_ratio)
{
    return (fmax(0, light_ratio * scalar_nl));
}

// final colour = original colour * (1 - reflectivity) + light colour * reflectivity
t_colour apply_light(t_colour original, t_colour light, float reflectivity)
{
    t_colour final_color;

    final_color.r = fmax(0, fmin(255, original.r * (1 - reflectivity) + light.r * reflectivity));
    final_color.g = fmax(0, fmin(255, original.g * (1 - reflectivity) + light.g * reflectivity));
    final_color.b = fmax(0, fmin(255, original.b * (1 - reflectivity) + light.b * reflectivity));
    final_color.a = 255;
    return (final_color);
}

// 1 Calculate normal, incident vectors a) from the lightpoint to the intersection point; b) from viewpoint (camera) to the intersection point
// 2 Calculate reflected vector
// 3 Calculate the specular light with a Phong model
// 4 Add the diffuse and ambient light
// 5 Apply the reflectivity to a pixel
int lighting(t_minirt *minirt)
{
    t_light_math light_inputs;
    int y;
    int x;
    int id;

    y = -1;
    while (++y < minirt->img_height)
    {
        x = -1;
        while (++x < minirt->img_width)
        {
            if (minirt->intersection[y][x])
            {
                id = minirt->intersection[y][x]->id;
                init_inputs(minirt->intersection[y][x], &light_inputs, minirt->scene->l.lightpoint, minirt->scene->c.point);
                if (is_in_shadow(minirt, &light_inputs, id)) {
                    light_inputs.reflectivity = minirt->scene->a.ratio;
                    // printf("Shadow hit the plane\n");
                    // minirt->pixels[y][x] = set_colour(0, 10, 0, 255);
                }
                else
                {
                    reflected_vector(&light_inputs);
                    specular_light(&light_inputs, minirt->scene->l.brightness);
                    light_inputs.reflectivity += minirt->scene->a.ratio + diffuse_light(light_inputs.scalar_nl, minirt->scene->l.brightness);
                    if (light_inputs.reflectivity > 1.0)
                        light_inputs.reflectivity = 1.0;
                    // draw_line(minirt, minirt->intersection[y][x]->point, minirt->scene->l.lightpoint, set_colour(255, 255, 255, 255));
                    // minirt->pixels[y][x] = set_colour(255, 0, 0, 255);
                }
                minirt->pixels[y][x] = apply_light(minirt->intersection[y][x]->colour, minirt->scene->l.colour, light_inputs.reflectivity);
            }
        }
    }
    return (0);
}
