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
    scene->background = set_colour(0, 0, 0, 255);
}

static int ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\f' || c == '\r' || c == '\v');
}

static char *normalise_whitespace(char *str)
{
	char *new_str;
	int i;

	new_str = malloc(ft_strlen(str) + 1);
	if (!new_str)
		return (NULL);
	i = 0;
	while (str[i])
	{
		if (ft_isspace(str[i]))
			new_str[i] = ' ';
		else
			new_str[i] = str[i];
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}

static t_scene *fill_scene(char **rows, int size)
{
	t_scene *scene;
	char **values;
	char *normalised;
	int i;

	scene = malloc(sizeof(t_scene));
	if (!scene)
		return (NULL);
	init_scene(scene);
	i = 0;
	while (i < size)
	{
		normalised = normalise_whitespace(rows[i]);
		if (!normalised)
			return (NULL);
		values = ft_split(normalised, ' ');
		free(normalised);
		if (!values)
		{
			printf("Error: ft_split failed.\n");
			return (NULL);
		}
		if (!*values)
		{
			i++;
			free(values);
			continue;
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
