/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhusieva <yhusieva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 14:13:09 by zpiarova          #+#    #+#             */
/*   Updated: 2025/05/09 17:53:08 by yhusieva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static void init_inputs(t_inter *intersection, t_light_math *vars, t_coord lightpoint, t_coord viewpoint)
{
    t_coord offset;

    vars->normal = get_surface_normal(intersection);
    normalize(&vars->normal);

    vars->shadow_ray = make_vector(intersection->point, lightpoint);
    vars->max_length = sqrtf(get_dot_product(vars->shadow_ray, vars->shadow_ray));
    normalize(&vars->shadow_ray);
    offset = multiply_vector_by_constant(vars->shadow_ray, EPSILON);
    vars->shadow_origin = move_point_by_vector(intersection->point, offset);

    vars->incident_l = make_vector(intersection->point, lightpoint);
    normalize(&vars->incident_l);
    vars->scalar_nl = get_dot_product(vars->incident_l, vars->normal);
    vars->incident_v = make_vector(viewpoint, intersection->point);
    normalize(&vars->incident_v);
    vars->reflectivity = 0.0;
}

// final colour = original colour * (1 - reflectivity) + light colour * reflectivity
static t_colour apply_light(t_colour original, t_colour light, float reflectivity)
{
    t_colour final_color;

    final_color.r = fmax(0, fmin(255, original.r * (1 - reflectivity) + light.r * reflectivity));
    final_color.g = fmax(0, fmin(255, original.g * (1 - reflectivity) + light.g * reflectivity));
    final_color.b = fmax(0, fmin(255, original.b * (1 - reflectivity) + light.b * reflectivity));
    final_color.a = 255;
    return (final_color);
}

static t_colour compute_pixel_light(t_scene *scene, t_inter *inter, t_coord lightpoint, t_coord viewpoint)
{
    t_light_math light_inputs;

    init_inputs(inter, &light_inputs, lightpoint, viewpoint);
    if (is_in_shadow(scene, &light_inputs, inter->id) || inter->id == -42)
        light_inputs.reflectivity = scene->a.ratio;
    else
    {
        if (inter->type != PLANE)
        {
            reflected_vector(&light_inputs);
            specular_light(&light_inputs, scene->l->brightness);
        }
        light_inputs.reflectivity += scene->a.ratio + diffuse_light(light_inputs.scalar_nl, scene->l->brightness);
        if (light_inputs.reflectivity > 1.0f)
            light_inputs.reflectivity = 1.0f;
    }
    return (apply_light(inter->colour, scene->l->colour, light_inputs.reflectivity));
}

int lighting(t_minirt *minirt)
{
    int y;
    int x;
    t_light *tmp_l;

    y = -1;
    while (++y < minirt->img_height)
    {
        x = -1;
        while (++x < minirt->img_width)
        {
            if (minirt->intersection[y][x])
            {
                tmp_l = minirt->scene->l;
                while (tmp_l)
                {
                    minirt->pixels[y][x] = compute_pixel_light(minirt->scene, minirt->intersection[y][x], minirt->scene->l->lightpoint, minirt->scene->c.point);
                    tmp_l = tmp_l->next;
                }
            }
        }
    }
    return (0);
}
