/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zuzanapiarova <zuzanapiarova@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 14:18:55 by zuzanapiaro       #+#    #+#             */
/*   Updated: 2025/04/26 19:39:10 by zuzanapiaro      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

// initilizes all allocated values in the scene to NULL
void	init_scene(t_scene *scene)
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
	scene->background = set_colour(200, 200, 200, 255);
}

// gets array of values from one file row
char	**row_values_into_arr(char *file_row)
{
	char	*normalised;
	char	**values;

	normalised = normalise_whitespace(file_row);
	if (!normalised || is_empty_line(normalised))
	{
		free(normalised);
		normalised = NULL;
		return (NULL);
	}
	values = ft_split(normalised, ' ');
	free(normalised);
	normalised = NULL;
	if (!values)
		return (NULL);
	return (values);
}

// iterates each line, normalizes whitespace, puts all elements into array, 
int	fill_scene(t_scene *scene, char **file_rows)
{
	char	**values;
	int		i;

	i = -1;
	while (file_rows[++i])
	{
		values = row_values_into_arr(file_rows[i]);
		if (!values)
			continue ;
		print_arr(values);
		if (!is_valid_input(values))
		{
			printf("Input contains invalid characters. Check the .rt file.\n");
			free_arr(values);
			return (ERROR);
		}
		if (identify_object(scene, values[0], values) == ERROR)
		{
			free_arr(values);
			return (ERROR);
		}
		free_arr(values);
	}
	return (SUCCESS);
}

// stores file rows into array, allocates scene and fills it with array data
// scene and its objects are freed in the caller function 
// returns allocated scene or NULL if alloc or fill fails
t_scene	*create_scene(char *filename)
{
	t_scene	*scene;
	char	**file_data;

	file_data = store_file_contents(filename);
	if (!file_data)
		return (NULL);
	scene = (t_scene *)malloc(sizeof(t_scene));
	if (!scene)
	{
		free_arr(file_data);
		return (NULL);
	}
	init_scene(scene);
	if (fill_scene(scene, file_data) == ERROR)
	{
		free_arr(file_data);
		free_scene(scene);
		return (NULL);
	}
	free_arr(file_data);
	scene->viewport_distance = 1.0;
	scene->viewport_width = get_viewport_width(scene->c.view_degree,
			scene->viewport_distance);
	scene->viewport_height = get_viewport_height(scene->viewport_width);
	return (scene);
}
