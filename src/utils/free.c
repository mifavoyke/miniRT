/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpiarova <zpiarova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 20:19:43 by zuzanapiaro       #+#    #+#             */
/*   Updated: 2025/04/28 14:20:00 by zpiarova         ###   ########.fr       */
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

// free the allocated objects in the scene (pl, cy, sp), and the scene itself
void	free_scene(t_scene *scene)
{
	t_sphere	*sp_tmp;
	t_plane		*pl_tmp;
	t_cylinder	*cy_tmp;

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
	scene = NULL;
}

void	free_list(t_inter **lst, void (*del)(void *))
{
	t_inter	*node;
	t_inter	*next;

	if (lst == NULL || *lst == NULL || del == NULL)
		return ;
	node = *lst;
	while (node)
	{
		next = node->next;
		free(node); // here is double free or corruption
		node = next;
	}
	*lst = NULL;
}

void	free_inter(t_inter ***section, int h, int w)
{
	int	y;
	int	x;

	y = -1;
	while (++y < h)
	{
		if (!section[y])
			continue ;
		x = -1;
		while (++x < w)
		{
			free_list(&section[y][x], free);
		}
		free(section[y]);
	}
	free(section);
	section = NULL;
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
