/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpiarova <zpiarova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 14:13:15 by zpiarova          #+#    #+#             */
/*   Updated: 2025/04/28 14:24:03 by zpiarova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

// prints possible key controls 
void print_controls(void)
{
    printf("\n=== MINI-RT CONTROLS ===\n");
    printf("Close Program:\n");
    printf("  [ESC]               → Exit the program\n\n");
    printf("Camera Position:\n");
    printf("  [W] / [S]           → Move camera forward/backward (Z-axis)\n");
    printf("  [A] / [D]           → Move camera left/right (X-axis)\n");
    printf("  Scroll              → Zoom in/out (Y-axis up/down)\n\n");
    printf("Camera Rotation:\n");
    printf("  [UP] / [DOWN]       → Pitch camera up/down (rotate X-axis)\n");
    printf("  [LEFT] / [RIGHT]    → Roll camera left/right (rotate Z-axis)\n");
    printf("  [J] / [K]           → Yaw camera left/right (rotate Y-axis)\n\n");
    printf("Additional:\n");
    printf("  Mouse Scroll        → Zoom camera in/out\n");
    printf("========================\n\n");
    printf("  Future: Add object control and light control if needed\n");
}

int minirt_init(t_minirt *minirt, t_scene *scene)
{
	minirt->scene = scene;
	minirt->img_width = WIDTH;
	minirt->img_height = HEIGHT;
	minirt->pixels = allocate_pixels(minirt->img_width, minirt->img_height, minirt->scene->background);
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
	// minirt->intersection = NULL;
	return (0);
}

void	cleanup(t_minirt *minirt)
{
	free_pixels(minirt->pixels, minirt->img_height);
	free_inter(minirt->intersection, minirt->img_height, minirt->img_width);
	free_scene(minirt->scene);
	mlx_delete_image(minirt->mlx, minirt->img);
	mlx_terminate(minirt->mlx);
}

int generate_image(t_minirt *minirt)
{
	shoot_rays(minirt, minirt->scene);
	lighting(minirt);
	render_pixels(minirt);
	return (0);
}

int32_t	main(int argc, char *argv[])
{
	t_scene		*scene;
	t_minirt	minirt;

	if (argc != 2)
		return (ft_error("Wrong input. Use:\t ./minirt [scene].rt\n"));
	scene = create_scene(argv[1]);
	if (!scene)
		return (ERROR);
	if (minirt_init(&minirt, scene) == ERROR)
	{
		free_scene(minirt.scene);
		return (ft_error(mlx_strerror(mlx_errno)));
	}
	if (generate_image(&minirt))
		return (ERROR);
	print_controls();
	
	mlx_loop_hook(minirt.mlx, ft_hook, (void *)&minirt);
	mlx_scroll_hook(minirt.mlx, &scroll_zoom, (void *)&minirt);
	mlx_resize_hook(minirt.mlx, resize_hook, (void *)&minirt);
	mlx_loop(minirt.mlx);

	cleanup(&minirt);
	return (0);
}
