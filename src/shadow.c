#include "../includes/minirt.h"

// inter_point ----> (hit?) ----> lightpoint

void debug_shadow_ray(t_coord ray_origin, t_coord ray_dir, t_sphere *sp, float t1, float t2, float max_distance)
{
	(void)sp;
    printf("SHADOW DEBUG:\n");
    printf("Ray origin:     (%f, %f, %f)\n", ray_origin.x, ray_origin.y, ray_origin.z);
    printf("Ray direction:  (%f, %f, %f)\n", ray_dir.x, ray_dir.y, ray_dir.z);
    // printf("  Sphere center:  (%f, %f, %f)\n", sp->centre.x, sp->centre.y, sp->centre.z);
    // printf("  Sphere radius:  %f\n", sp->diameter / 2.0);
    printf("t1 = %f, t2 = %f\n", t1, t2);
    printf("max_distance:   %f\n", max_distance);
}

bool does_ray_intersect_sphere(t_coord ray_origin, t_coord ray_dir, t_sphere *sp, float max_distance)
{
	t_coord oc = make_vector(ray_origin, sp->centre);
	float radius = sp->diameter / 2.0;
	float a = get_dot_product(ray_dir, ray_dir);
	float b = 2.0 * get_dot_product(oc, ray_dir);
	float c = get_dot_product(oc, oc) - radius * radius;
	float discriminant = b * b - 4 * a * c;
	
	if (discriminant <= 0)
		return (false);
	float sqrt_d = sqrtf(discriminant);
	float t1 = fabs((-b - sqrt_d) / (2 * a));
	float t2 = fabs((-b + sqrt_d) / (2 * a));
	if ((t1 > 0.001 && t1 < max_distance) || (t2 > 0.001 && t2 < max_distance))
		return (true);
	return (false);
}

int is_in_shadow(t_minirt *minirt, t_light_math *light_inputs, int current_id)
{
	// float t;
	// t_plane *tmp_pl;
	t_sphere *tmp_sp;

	tmp_sp = minirt->scene->sp;
	while (tmp_sp)
	{
		if (tmp_sp->id == current_id) 
			return (0);
		if (does_ray_intersect_sphere(light_inputs->shadow_origin, light_inputs->shadow_ray, tmp_sp, light_inputs->max_length))
			return (1);
		tmp_sp = tmp_sp->next;
	}
	// tmp_pl = minirt->scene->pl;
	// while (tmp_pl)
	// {
	// 	t = get_plane_intersection_t(light_inputs->shadow_ray, light_inputs->shadow_origin, tmp_pl);
	// 	if (t > 0.001 && t < light_inputs->max_length)
	// 		return (1);
	// 	tmp_pl = tmp_pl->next;
	// }
	return (0);
}