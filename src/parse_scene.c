#include "../includes/minirt.h"

static void init_scene(t_scene *scene)
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
}

static t_scene *fill_scene(char **rows, int size)
{
	t_scene *scene;
	char **values;
	int i;

	scene = malloc(sizeof(t_scene));
	if (!scene)
		return (NULL);
	init_scene(scene);
	i = 0;
	while (i < size)
	{
		values = ft_split(rows[i], ' ');
		if (!values)
		{
			printf("Error: ft_split failed.\n");
			return (NULL);
		}
		if (valid_input(values))
		{
			ft_free(values);
			return (NULL);
		}
		if (identify_objects(scene, values[0], values))
		{
			ft_free(values);
			return (NULL);
		}
		ft_free(values);
		i++;
	}
	return (scene);
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
	// ft_free(parsed_file);
	if (!minirt->scene)
		return (1);
	return (0);
}
