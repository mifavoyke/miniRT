/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zuzanapiarova <zuzanapiarova@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 12:50:50 by zuzanapiaro       #+#    #+#             */
/*   Updated: 2025/04/18 12:50:51 by zuzanapiaro      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void free_arr(char **arr)
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

void	free_section(t_inter **lst, void (*del)(void *)) // took ft_lstclear from libft and adjusted
{
	t_inter	*node;
	t_inter	*next;

	if (lst == NULL || *lst == NULL || del == NULL)
		return ;
	node = *lst;
	while (node)
	{
		next = node->next;
		free(node);
		node = next;
	}
	*lst = NULL;
}

void free_inter(t_inter ***section, int h, int w)
{
	int y;
	int x;

	y = -1;
	while (++y < h)
	{
		if (!section[y])
			continue;
		x = -1;
		while (++x < w)
		{
			free_section(&section[y][x], free);
		}
		free(section[y]);
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
