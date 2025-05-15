/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong_model.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zuzanapiarova <zuzanapiarova@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 23:21:40 by zuzanapiaro       #+#    #+#             */
/*   Updated: 2025/05/15 23:26:18 by zuzanapiaro      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

// calculates the closest point on the cylinder axis and finds the vector from
// that closest point on the axis to the intersection point
static t_coord	calculate_cylider_normal(t_cylinder *cy, t_coord inter_point)
{
	t_coord	closest_axis_point;
	t_coord	normal;
	int		t;

	t = dot(make_vector(cy->centre, inter_point), cy->axis);
	closest_axis_point = get_point_on_vector(cy->centre, cy->axis, t);
	normal = make_vector(closest_axis_point, inter_point);
	return (normal);
}

t_coord	get_surface_normal(t_inter *intersection)
{
	t_sphere	*sp;
	t_plane		*pl;
	t_cylinder	*cy;

	if (intersection->type == SPHERE)
	{
		sp = (t_sphere *)intersection->obj;
		return (make_vector(sp->centre, intersection->point));
	}
	else if (intersection->type == PLANE)
	{
		pl = (t_plane *)intersection->obj;
		return (set_coord(pl->vector.x, pl->vector.y, pl->vector.z));
	}
	else if (intersection->type == CYLINDER)
	{
		cy = (t_cylinder *)intersection->obj;
		if (cy->axis.z == 1 || cy->axis.z == -1)
			return (make_vector(cy->centre, intersection->point));
		else
			return (calculate_cylider_normal(cy, intersection->point));
	}
	return (set_coord(0, 0, 0));
}

// bidirectional reflectance distribution function (BRDF)
// reflected vector: R = I − 2*N *(I*N)
t_coord	reflected_vector(t_light_math *inputs)
{
	t_coord	scaled_normal_vector;

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
	inputs->reflectivity = fmax(0, (light_brightness * pow(inputs->scalar_vr,
					REFLECTION)));
	return (inputs->reflectivity);
}

// Lambertian reflectance for diffuse light: Id = max{0, k * (N*L)}
float	diffuse_light(float scalar_nl, float light_ratio)
{
	// printf("scalar nl: %f light ratio: %f, result: %f\n", scalar_nl, light_ratio, scalar_nl * light_ratio);
	return (fmax(0, light_ratio * scalar_nl));
}
