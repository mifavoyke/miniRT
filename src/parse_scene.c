#include "../includes/minirt.h"

int default_scene(t_scene *scene)
{
	scene->sp = NULL;
	scene->pl = NULL;
	scene->cy = NULL;
	scene->a_count = 0;
    scene->c_count = 0;
    scene->l_count = 0;
    scene->sp_count = 0;
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
	// free(minirt->scene);
	// ft_free(parsed_file, size);
	return (0);
}
