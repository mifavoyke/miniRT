/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zuzanapiarova <zuzanapiarova@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 14:11:41 by zpiarova          #+#    #+#             */
/*   Updated: 2025/04/17 22:08:56 by zuzanapiaro      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

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
	scene->background = set_colour(200, 200, 200, 255); // light gray, can we set it as a macro somehow?
}

static int ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\f' || c == '\r' || c == '\v');
}

static char *normalise_whitespace(char *str)
{
	char *new_str;
	int i = 0;
	int j = 0;

	new_str = malloc(ft_strlen(str) + 1);
	if (!new_str)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '#')
		{
			while (str[i] && str[i] != '\n')
				i++;
			break;
		}
		else if (ft_isspace(str[i]))
			new_str[j++] = ' ';
		else
			new_str[j++] = str[i];

		i++;
	}
	new_str[j] = '\0';
	return (new_str);
}

// iterates each line, normalizes whitespace, puts all elements into array, 
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
		{
			free(scene);
			scene = NULL;
			return (NULL);
		}
		values = ft_split(normalised, ' ');
		free(normalised);
		if (!values)
		{
			free(scene);
			scene = NULL;
			printf("Error: ft_split failed.\n");
			return (NULL);
		}
		if (!*values)
		{
			i++;
			free(values);
			continue ;
		}
		if (valid_input(values))
		{
			free_arr(values);
			return (NULL);
		}
		if (identify_objects(scene, values[0], values))
		{
			free_arr(values);
			return (NULL);
		}
		free_arr(values);
		i++;
	}
	return (scene);
}

int create_scene(t_minirt *minirt, char *rt_file)
{
	char **parsed_file;
	int size;

	size = count_rows(rt_file);
	parsed_file = get_lines(rt_file, size);
	if (!parsed_file)
		return (ERROR);
	minirt->scene = fill_scene(parsed_file, size);
	free(parsed_file);
	if (!minirt->scene)
		return (ERROR);
	minirt->scene->viewport_distance = 1.0;
	minirt->scene->viewport_width = get_viewport_width(minirt->scene->c.view_degree, minirt->scene->viewport_distance);
	minirt->scene->viewport_height = get_viewport_height(minirt->scene->viewport_width);
	return (0);
}
