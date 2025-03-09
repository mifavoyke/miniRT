#include "../includes/minirt.h"

void default_ambient(t_ambient *a)
{
	a->ratio = 0.2;
	a->colour = set_colour(255, 51, 255);
}

void default_camera(t_camera *c)
{
	c->viewpoint = set_coord(-50.0, 0.0, 20.0);
	c->vector = set_coord(0.0, 0.0, 1.0);
	c->view_degree = 70;
}

void default_light(t_light *l)
{
	l->lightpoint = set_coord(-40.0, 50.0, 0.0);
	l->brightness = 0.6;
	l->colour = set_colour(255, 255, 255);
}

int default_scene(t_scene *scene)
{
	default_ambient(&scene->a);
	default_camera(&scene->c);
	default_light(&scene->l);

	scene->sp = malloc(sizeof(t_sphere));
	if (!scene->sp)
		return (1);
	create_test_sphere(scene->sp);
	
	// scene->sp = NULL;
	scene->pl = NULL;
	scene->cy = NULL;
	scene->sp_count = 1;
	scene->pl_count = 0;
	scene->cy_count = 0;
	return (0);
}

int parse_scene(t_minirt *minirt, char *rt_file)
{
	char **parsed_file;
	int size;

	size = count_rows(rt_file);
	parsed_file = get_lines(rt_file, size);
	if (!parsed_file)
		return (1);

	minirt->scene = fill_scene(parsed_file, size);
	if (!minirt->scene)
	{
		// free(minirt->scene);
		// ft_free(parsed_file, size);
		return (1);
	}

	print_scene(minirt->scene);
	free(minirt->scene->sp);

	free(minirt->scene);
	ft_free(parsed_file, size);
	return (0);
}
