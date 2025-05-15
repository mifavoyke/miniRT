#include "../../includes/minirt.h"

static t_colour	compute_light_contribution(t_scene *scene,
	t_inter *inter, t_light *l, t_coord viewpoint)
{
	t_light_math	inputs;
	float			is_inside;

	init_inputs(inter, &inputs, l->lightpoint, viewpoint);
	is_inside = dot(inputs.normal, inputs.incident_v);
	if (is_in_shadow(scene, &inputs, inter->id)
		|| inter->id == -42 || inputs.scalar_nl <= EPS || is_inside >= EPS)
		inputs.reflectivity = 0.0f;
	else
	{
		if (inter->type != PLANE)
		{
			reflected_vector(&inputs);
			specular_light(&inputs, l->brightness);
		}
		inputs.reflectivity += diffuse_light(inputs.scalar_nl, l->brightness);
		if (inputs.reflectivity > 1.0f)
			inputs.reflectivity = 1.0f;
	}
	return (add_light_contribution(inter->colour,
			l->colour, inputs.reflectivity));
}

static t_colour	compute_pixel_light(t_scene *scene, t_inter *intersection)
{
	t_colour	accumulated;
	t_colour	light_contrib;
	t_light		*tmp_l;

	tmp_l = scene->l;
	accumulated = apply_light(intersection->colour,
			scene->a.colour, scene->a.ratio);
	while (tmp_l)
	{
		light_contrib = compute_light_contribution(scene,
				intersection, tmp_l, scene->c.point);
		accumulated.r = fmin(255, accumulated.r + light_contrib.r);
		accumulated.g = fmin(255, accumulated.g + light_contrib.g);
		accumulated.b = fmin(255, accumulated.b + light_contrib.b);
		tmp_l = tmp_l->next;
	}
	return (accumulated);
}

int	lighting(t_minirt *minirt)
{
	int	y;
	int	x;

	y = -1;
	while (++y < minirt->img_height)
	{
		x = -1;
		while (++x < minirt->img_width)
		{
			if (minirt->intersection[y][x])
			{
				minirt->pixels[y][x] = compute_pixel_light(minirt->scene,
						minirt->intersection[y][x]);
			}
		}
	}
	return (0);
}
