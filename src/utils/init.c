/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpiarova <zpiarova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 15:07:24 by zpiarova          #+#    #+#             */
/*   Updated: 2025/04/29 12:24:11 by zpiarova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

// prints possible key controls 
void print_controls(void)
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

int minirt_init(t_minirt *minirt, t_scene *scene)
{
	minirt->scene = scene;
	minirt->img_width = WIDTH;
	minirt->img_height = HEIGHT;
	minirt->pixels = allocate_pixels(minirt->img_width,
			minirt->img_height, minirt->scene->background);
	if (!minirt->pixels)
		return (ERROR);
	minirt->intersection = allocate_inter(minirt->img_width, minirt->img_height);
	if (!minirt->intersection)
	{
		free_pixels(minirt->pixels, minirt->img_height);
		return (ERROR);
	}
	minirt->mlx = mlx_init(WIDTH, HEIGHT, "miniRT", true);
	if (!minirt->mlx)
		return (ERROR);
	minirt->img = mlx_new_image(minirt->mlx, minirt->img_width, minirt->img_height);
	if (!minirt->img || (mlx_image_to_window(minirt->mlx, minirt->img, 0, 0) < 0))
		return (ERROR);
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
	scene->background = set_colour(200, 200, 200, 255);
}