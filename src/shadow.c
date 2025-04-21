#include "../includes/minirt.h"

// inter_point ----> (hit?) ----> lightpoint

bool does_ray_intersect_sphere(t_coord ray_origin, t_coord ray_dir, t_sphere *sp, float max_distance)
{
	t_coord oc = make_vector(ray_origin, sp->centre);
	float radius = sp->diameter / 2.0;
	float a = get_dot_product(ray_dir, ray_dir);
	float b = 2.0 * get_dot_product(oc, ray_dir);
	float c = get_dot_product(oc, oc) - radius * radius;
	float discriminant = b * b - 4 * a * c;

	if (discriminant < 0)
		return (false);
	float sqrt_d = sqrtf(discriminant);
	float t1 = (-b - sqrt_d) / (2 * a);
	float t2 = (-b + sqrt_d) / (2 * a);
	if ((t1 > 0.001 && t1 < max_distance) || (t2 > 0.001 && t2 < max_distance))
		return (true);
	return (false);
}

// t = dot(p0 - ray_origin, n) / dot(ray_dir, n)
int does_ray_intersect_plane(t_coord ray_origin, t_coord ray_dir, t_plane *pl, float max_length)
{
	t_coord vector_to_obj;
	float denominator;
	float t;

	denominator = get_dot_product(ray_dir, pl->vector);
	if (fabs(denominator) < 1e-6) // ray parallele to the plane
		return (0);
	vector_to_obj = make_vector(ray_origin, pl->point);
	t = get_dot_product(vector_to_obj, pl->vector) / denominator;
	if (t > 0.001 && t < max_length)
		return (1);
	return (0);
}

int is_in_shadow(t_minirt *minirt, t_light_math *light_inputs)
{
	t_plane *tmp_pl;
	t_sphere *tmp_sp;

	if (minirt->scene->sp)
	{
		tmp_sp = minirt->scene->sp;
		while (tmp_sp)
		{
			if (does_ray_intersect_sphere(light_inputs->shadow_origin, light_inputs->shadow_ray, tmp_sp, light_inputs->max_length))
				return (1);
			tmp_sp = tmp_sp->next;
		}
	}
	if (minirt->scene->pl)
	{
		tmp_pl = minirt->scene->pl;
		while (tmp_pl)
		{
			if (does_ray_intersect_plane(light_inputs->shadow_origin, light_inputs->shadow_ray, tmp_pl, light_inputs->max_length))
				return (1);
			tmp_pl = tmp_pl->next;
		}
	}
	return (0);
}