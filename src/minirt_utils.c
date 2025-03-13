/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpiarova <zpiarova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 17:06:31 by zpiarova          #+#    #+#             */
/*   Updated: 2025/03/13 17:06:33 by zpiarova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int ft_error(const char *msg)
{
    printf("Error: %s\n", msg);
    return (1);
}

void ft_free(char **arr)
{
    int i;

    i = 0;
    while (arr[i])
    {
        free(arr[i]);
        i++;
    }
    free(arr);
}

void free_scene(t_scene *scene)
{
	int i;

	if (scene->sp)
	{
		i = 0;
		while (i < scene->sp_count)
		{
			free(scene->sp);
			i++;
		}
	}
	if (scene->pl)
	{
		i = 0;
		while (i < scene->pl_count)
		{
			free(scene->pl);
			i++;
		}
	}
	if (scene->cy)
	{
		i = 0;
		while (i < scene->cy_count)
		{
			free(scene->cy);
			i++;
		}
	}
	free(scene);
}

int valid_coord(t_coord *coord)
{
    return (coord->x == INT_ERROR && coord->y == INT_ERROR && coord->z == INT_ERROR);
}

int valid_colour(t_colour *clr)
{
    return (clr->r == -1 && clr->r == -1 && clr->r == -1);
}

int check_file_format(char *filename)
{
	int i;

	i = 0;
	while (filename[i])
	{
		if (filename[i] == '.' && filename[i + 1] == 'r' && filename[i + 2] == 't' && filename[i + 3] == '\0')
			return (0);
		i++;
	}
	return (1);
}
