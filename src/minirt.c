/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zuzanapiarova <zuzanapiarova@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 14:13:15 by zpiarova          #+#    #+#             */
/*   Updated: 2025/04/17 21:22:45 by zuzanapiaro      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int minirt_init(t_minirt *minirt)
{
	minirt->img_width = 1920;
	minirt->img_height = 1080;
	// mlx_set_setting(MLX_MAXIMIZED, true);
	minirt->mlx = mlx_init(WIDTH, HEIGHT, "miniRT", true);
	if (!minirt->mlx)
		return (ERROR);
	minirt->img = mlx_new_image(minirt->mlx, minirt->img_width, minirt->img_height);
	if (!minirt->img || (mlx_image_to_window(minirt->mlx, minirt->img, 0, 0) < 0))
		return (ERROR);
	minirt->intersection = NULL;
	minirt->pixels = allocate_pixels(minirt->img_width, minirt->img_height);
	if (!minirt->pixels)
		return (ERROR);
	return (0);
}

void generate_image(t_minirt *minirt) // should we do it void or consider some failure cases?
{
	if (minirt->intersection)
		free_inter(minirt->intersection, minirt->img_height, minirt->img_width);
	init_pixels(minirt);
	shoot_rays(minirt, minirt->scene);
	// print_intersections(minirt->intersection, minirt->img_width, minirt->img_height);
	lighting(minirt);
	render_pixels(minirt);
}

int32_t main(int argc, char *argv[])
{
	t_minirt minirt;
	
	if (argc != 2)
		return (ft_error("Usage: ./miniRT [scene].rt"));
	if (check_file_format(argv[1]))
		return (ft_error("Wrong scene format. Expected .rt file."));
	if (create_scene(&minirt, argv[1]))
		return (ERROR);
	if (minirt_init(&minirt))
	{
		// TODO: free the scene
		return (ft_error(mlx_strerror(mlx_errno)));
	}
	generate_image(&minirt);

	mlx_loop_hook(minirt.mlx, ft_hook, (void *)&minirt);
	mlx_loop(minirt.mlx);

	free_inter(minirt.intersection, minirt.img_height, minirt.img_width);
	free_scene(minirt.scene);
	free_pixels(minirt.pixels, minirt.img_height);
	
	mlx_delete_image(minirt.mlx, minirt.img);
	mlx_terminate(minirt.mlx);
	return (0);
}
