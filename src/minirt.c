/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhusieva <yhusieva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 14:13:15 by zpiarova          #+#    #+#             */
/*   Updated: 2025/04/23 19:43:46 by yhusieva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int minirt_init(t_minirt *minirt)
{
	minirt->img_width = WIDTH;
	minirt->img_height = HEIGHT;
	minirt->mlx = mlx_init(WIDTH, HEIGHT, "miniRT", true);
	if (!minirt->mlx)
		return (ERROR);
	minirt->img = mlx_new_image(minirt->mlx, minirt->img_width, minirt->img_height);
	if (!minirt->img || (mlx_image_to_window(minirt->mlx, minirt->img, 0, 0) < 0))
		return (ERROR);
	minirt->intersection = NULL;
	return (0);
}

int generate_image(t_minirt *minirt)
{
	if (init_pixels(minirt))
		return (ERROR);
	minirt->intersection = allocate_inter(minirt->img_width, minirt->img_height);
	if (!minirt->intersection)
		return (ERROR);
	shoot_rays(minirt, minirt->scene);
	lighting(minirt);
	render_pixels(minirt);
	return (0);
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

	free_inter(minirt.intersection, minirt.img_height, minirt.img_width);
	free_pixels(minirt.pixels, minirt.img_height);
	free_scene(minirt.scene);
	
	mlx_delete_image(minirt.mlx, minirt.img);
	mlx_terminate(minirt.mlx);
	return (0);
}
