/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhusieva <yhusieva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 14:13:09 by zpiarova          #+#    #+#             */
/*   Updated: 2025/05/15 17:25:10 by yhusieva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static void init_inputs(t_inter *intersection, t_light_math *vars, t_coord lightpoint, t_coord viewpoint)
{
    t_coord offset;

    vars->normal = get_surface_normal(intersection);
    normalize(&vars->normal);
    vars->shadow_ray = make_vector(intersection->point, lightpoint);
    vars->max_length = sqrtf(dot(vars->shadow_ray, vars->shadow_ray));
    normalize(&vars->shadow_ray);
    offset = mult_vector_by_c(vars->shadow_ray, EPS);
    vars->shadow_origin = move_point_by_vector(intersection->point, offset);
    vars->incident_l = make_vector(intersection->point, lightpoint);
    normalize(&vars->incident_l);
    vars->scalar_nl = dot(vars->incident_l, vars->normal);
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

static t_colour add_light_contribution(t_colour base, t_colour light, float intensity)
{
	t_colour result;

	result.r = base.r * (light.r / 255) * intensity;
	result.g = base.g * (light.g / 255) * intensity;
	result.b = base.b * (light.b / 255) * intensity;
    printf("Mixing: base(%d, %d, %d) + light(%d, %d, %d) * %f\n",
       base.r, base.g, base.b, light.r, light.g, light.b, intensity);
	return (result);
}

static t_colour compute_light_contribution(t_scene *scene, t_inter *inter, t_light *l, t_coord viewpoint)
{
    t_light_math light_inputs;

    init_inputs(inter, &light_inputs, l->lightpoint, viewpoint);
    if (is_in_shadow(scene, &light_inputs, inter->id) || inter->id == -42 || light_inputs.scalar_nl <= EPS || (dot(light_inputs.normal, light_inputs.incident_v) >= 0.5))
        light_inputs.reflectivity = 0.0f;
    else
    {
        if (inter->type != PLANE)
        {
            reflected_vector(&light_inputs);
            specular_light(&light_inputs, l->brightness);
        }
        light_inputs.reflectivity += diffuse_light(light_inputs.scalar_nl, l->brightness);
        if (light_inputs.reflectivity > 1.0f)
            light_inputs.reflectivity = 1.0f;
    }
    return (add_light_contribution(inter->colour, l->colour, light_inputs.reflectivity));
}

static t_colour compute_pixel_light(t_scene *scene, t_inter *intersection)
{
    t_colour accumulated;
    t_colour light_contrib;
    t_light *tmp_l;

    tmp_l = scene->l;
    accumulated = apply_light(intersection->colour, scene->a.colour, scene->a.ratio);
    while (tmp_l)
    {
        light_contrib = compute_light_contribution(scene, intersection, tmp_l, scene->c.point);
        accumulated.r = fmin(255, accumulated.r + light_contrib.r);
        accumulated.g = fmin(255, accumulated.g + light_contrib.g);
        accumulated.b = fmin(255, accumulated.b + light_contrib.b);
        // printf("Final pixel color: (%d, %d, %d)\n", accumulated.r, accumulated.g, accumulated.b);
        tmp_l = tmp_l->next;
    }
    return (accumulated);
}

int lighting(t_minirt *minirt)
{
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
                minirt->pixels[y][x] = compute_pixel_light(minirt->scene, minirt->intersection[y][x]);
                // printf("Pixel[%d,%d] Final = (%d, %d, %d)\n", x, y, minirt->pixels[y][x].r, minirt->pixels[y][x].g, minirt->pixels[y][x].b);
            }
        }
    }
    return (0);
}
