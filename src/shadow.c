#include "../includes/minirt.h"

bool is_there_intersection(t_scene *scene, t_coord ray);
int is_in_shadow(t_minirt *minirt, t_light_math *light_inputs);

bool is_there_intersection(t_scene *scene, t_coord ray)
{
	t_sphere *temp_sp; // maybe create a void * list of objects - spheres,planes, cylinders
	t_plane *temp_pl;
	t_cylinder *temp_cy;
    t_inter *new_node;
    
	temp_sp = scene->sp;
	temp_cy = scene->cy;
	temp_pl = scene->pl;
	while (temp_sp)
	{
		new_node = find_sphere_intersections(ray, scene->c, temp_sp, scene->l.lightpoint);
		if (new_node)
        {
            free(new_node);
			return true;
        }
		temp_sp = temp_sp->next;
	}
	while (temp_cy)
	{
		new_node = find_cylinder_intersections(ray, scene->c, temp_cy, scene->l.lightpoint);
		if (new_node)
        {
            free(new_node);
			return true;
        }
		temp_cy = temp_cy->next;
	}
	while (temp_pl)
	{
		new_node = find_plane_intersections(ray, scene->c, temp_pl, scene->l.lightpoint);
		if (new_node)
        {
            free(new_node);
			return true;
        }
		temp_pl = temp_pl->next;
	}
	return (false);
}

// int is_in_shadow(t_minirt *minirt, t_light_math *light_inputs)
// {
//     float d;

//     d = get_dot_product(light_inputs->actual_v_to_l, light_inputs->actual_v_to_l);
//     // if (compare_distance(minirt, light_inputs->incident_l, d))
//     //     return (1);
//     // else
//     //     return (0);
// }
