/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong_model.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhusieva <yhusieva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 15:39:42 by yhusieva          #+#    #+#             */
/*   Updated: 2025/05/20 17:58:16 by yhusieva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

// bidirectional reflectance distribution function (BRDF)
// reflected vector: R = I − 2*N *(I*N)
t_coord	reflected_vector(t_light_math *inputs)
{
	t_coord		scaled_normal_vector;

	scaled_normal_vector = mult_vector_by_c(inputs->normal,
			2 * inputs->scalar_nl);
	inputs->reflected_vector = subtract_vectors(inputs->incident_l,
			scaled_normal_vector);
	return (inputs->reflected_vector);
}

// Phong reflection model for specular light: Is = max{0, k * (R*V)^n}
float	specular_light(t_light_math *inputs, float light_brightness)
{
	inputs->scalar_vr = dot(inputs->reflected_vector, inputs->incident_v);
	inputs->reflectivity = fmax(0,
			(light_brightness * pow(inputs->scalar_vr, REFLECTION)));
	return (inputs->reflectivity);
}

// Lambertian reflectance for diffuse light: Id = max{0, k * (N*L)}
float	diffuse_light(float scalar_nl, float light_ratio)
{
	return (fmax(0, light_ratio * scalar_nl));
}

// final colour = 
// original colour * (1 - reflectivity) + light colour * reflectivity
t_colour	apply_light(t_colour original, t_colour light, float reflectivity)
{
	t_colour	final_color;

	final_color.r = fmax(0, fmin(255,
				original.r * (1 - reflectivity) + light.r * reflectivity));
	final_color.g = fmax(0, fmin(255,
				original.g * (1 - reflectivity) + light.g * reflectivity));
	final_color.b = fmax(0, fmin(255,
				original.b * (1 - reflectivity) + light.b * reflectivity));
	final_color.a = 255;
	return (final_color);
}

t_colour	add_light_contribution(t_colour base,
	t_colour light, float intensity)
{
	t_colour	result;

	result.r = base.r * (light.r / 255) * intensity;
	result.g = base.g * (light.g / 255) * intensity;
	result.b = base.b * (light.b / 255) * intensity;
	return (result);
}
