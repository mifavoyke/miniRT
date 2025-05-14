/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zuzanapiarova <zuzanapiarova@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 15:07:24 by zpiarova          #+#    #+#             */
/*   Updated: 2025/05/14 09:27:03 by zuzanapiaro      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

int	minirt_init(t_minirt *rt, t_scene *scene)
{
	rt->scene = scene;
	rt->img_width = WIDTH;
	rt->img_height = HEIGHT;
	rt->pixels = allocate_pixels(rt->img_width,
			rt->img_height, rt->scene->bg);
	if (!rt->pixels)
		return (ERROR);
	rt->intersection = allocate_inter(rt->img_width, rt->img_height);
	if (!rt->intersection)
	{
		free_pixels(rt->pixels, rt->img_height);
		return (ERROR);
	}
	rt->mlx = mlx_init(WIDTH, HEIGHT, "miniRT", true);
	if (!rt->mlx)
		return (ERROR);
	rt->img = mlx_new_image(rt->mlx, rt->img_width, rt->img_height);
	if (!rt->img || (mlx_image_to_window(rt->mlx, rt->img, 0, 0) < 0))
		return (ERROR);
	print_controls();
	return (SUCCESS);
}

// initilizes all allocated values in the scene to NULL
void	init_scene(t_scene *scene)
{
	scene->l = NULL;
	scene->light_spheres = NULL;
	scene->sp = NULL;
	scene->pl = NULL;
	scene->cy = NULL;
	scene->a_count = 0;
	scene->c_count = 0;
	scene->bg = set_colour(200, 200, 200, 255);
}

// sets object lists from scene to objects struct
t_objs	set_objects(t_scene *scene)
{
	t_objs	objs;

	objs.sp = scene->sp;
	objs.cy = scene->cy;
	objs.pl = scene->pl;
	objs.sun = scene->light_spheres;
	objs.light = scene->l;
	return (objs);
}
