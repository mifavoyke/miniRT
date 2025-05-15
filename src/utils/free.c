/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpiarova <zpiarova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 20:19:43 by zuzanapiaro       #+#    #+#             */
/*   Updated: 2025/05/15 16:39:21 by zpiarova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

// frees the array
void	free_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	arr = NULL;
}

// helper functoin that frees the lights and light spheres from the scene
void	free_lights(t_scene *scene, t_objs *tmp)
{
	while (scene->light_spheres)
	{
		tmp->sun = scene->light_spheres->next;
		free(scene->light_spheres);
		scene->light_spheres = tmp->sun;
	}
	while (scene->l)
	{
		tmp->light = scene->l->next;
		free(scene->l);
		scene->l = tmp->light;
	}
}

// free the allocated objects in the scene (pl, cy, sp, lights, light spheres)
// and free the scene itself
void	free_scene(t_scene *scene)
{
	t_objs	tmp;

	tmp = set_objects(scene);
	while (scene->sp)
	{
		tmp.sp = scene->sp->next;
		free(scene->sp);
		scene->sp = tmp.sp;
	}
	while (scene->pl)
	{
		tmp.pl = scene->pl->next;
		free(scene->pl);
		scene->pl = tmp.pl;
	}
	while (scene->cy)
	{
		tmp.cy = scene->cy->next;
		free(scene->cy);
		scene->cy = tmp.cy;
	}
	free_lights(scene, &tmp);
	free(scene);
	scene = NULL;
}

void	free_inter(t_inter ***intersection, int h, int w)
{
	int	y;
	int	x;

	y = -1;
	while (++y < h)
	{
		if (!intersection[y])
			continue ;
		x = -1;
		while (++x < w)
		{
			free_list(&intersection[y][x], free);
		}
		free(intersection[y]);
	}
	free(intersection);
	intersection = NULL;
}

void	free_pixels(t_colour **p, int h)
{
	int	y;

	y = 0;
	while (y < h)
	{
		free(p[y]);
		y++;
	}
	free(p);
	p = NULL;
}
