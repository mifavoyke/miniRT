/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpiarova <zpiarova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 15:07:24 by zpiarova          #+#    #+#             */
/*   Updated: 2025/04/30 17:18:47 by zpiarova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

// prints possible key controls 
void	print_controls(void)
{
	printf("\n=== MINI-RT CONTROLS ===\n");
	printf("Close Program:\n");
	printf("  [ESC]             → Exit the program\n");
	printf("Camera Position:\n");
	printf("  [W] / [S]         → Move camera up/down (Z-axis)\n");
	printf("  [A] / [D]         → Move camera left/right (X-axis)\n");
	printf("  Scroll            → Zoom in/out (Y-axis forward/back)\n");
	printf("Camera Rotation:\n");
	printf("  [UP] / [DOWN]     → Pitch (rotate around X-axis - up/down)\n");
	printf("  [J] / [K]         → Roll (rotate Y-axis - tilt to sides)\n");
	printf("  [LEFT] / [RIGHT]  → Yaw (rotate around Z-axis-left/right)\n");
	printf("========================\n");
}

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
	return (0);
}

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
	scene->bg = set_colour(200, 200, 200, 255);
}
