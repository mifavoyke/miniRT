/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhusieva <yhusieva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 17:06:31 by zpiarova          #+#    #+#             */
/*   Updated: 2025/03/21 13:16:23 by yhusieva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

int ft_error(const char *msg)
{
	printf("Error: %s\n", msg);
	return (ERROR);
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
	t_sphere *sp_tmp;
	t_plane *pl_tmp;
	t_cylinder *cy_tmp;

	while (scene->sp)
	{
		sp_tmp = scene->sp->next;
		free(scene->sp);
		scene->sp = sp_tmp;
	}
	while (scene->pl)
	{
		pl_tmp = scene->pl->next;
		free(scene->pl);
		scene->pl = pl_tmp;
	}
	while (scene->cy)
	{
		cy_tmp = scene->cy->next;
		free(scene->cy);
		scene->cy = cy_tmp;
	}
	free(scene);
}

void free_inter(t_inter ***section, int h, int w)
{
	int y;
	(void)w;

	y = 0;
	while (y < h)
	{
		free(section[y]);
		y++;
	}
	free(section);
}

void free_pixels(t_colour **p, int h)
{
	int y;

	y = 0;
	while (y < h)
	{
		free(p[y]);
		y++;
	}
	free(p);
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
