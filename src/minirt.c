/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhusieva <yhusieva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 16:37:45 by yhusieva          #+#    #+#             */
/*   Updated: 2025/03/13 18:19:22 by yhusieva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void draw_line(mlx_image_t *image)
{
	int i = 50;

	while (i < 100)
	{
		mlx_put_pixel(image, i, i, 0xe5f89f);
		i++;
	}
}

int minirt_init(t_minirt *minirt)
{
	minirt->img_width = 1920;
	minirt->img_height = 1080;
	// mlx_set_setting(MLX_MAXIMIZED, true);
	minirt->mlx = mlx_init(WIDTH, HEIGHT, "miniRT", true);
	if (!minirt->mlx)
		return (1);
	minirt->img = mlx_new_image(minirt->mlx, minirt->img_width, minirt->img_height);
	if (!minirt->img || (mlx_image_to_window(minirt->mlx, minirt->img, 0, 0) < 0))
		return (1);
	return (0);
}

int32_t main(int argc, char *argv[])
{
	t_minirt minirt;

	if (argc != 2)
		return (ft_error("Usage: ./miniRT [scene].rt"));
	if (check_file_format(argv[1]))
		return (ft_error("Wrong scene format. Expected .rt file."));
	if (minirt_init(&minirt))
		return (ft_error(mlx_strerror(mlx_errno)));
	if (parse_scene(&minirt, argv[1]))
	{
		mlx_delete_image(minirt.mlx, minirt.img);
		mlx_terminate(minirt.mlx);
		return (1);
	}
	print_scene(minirt.scene);

	minirt.scene->viewport = set_viewport_plane(*minirt.scene);
	shoot_rays(minirt.img, minirt.scene, minirt.scene->sp);

	mlx_loop_hook(minirt.mlx, ft_hook, (void *)&minirt);
	mlx_loop(minirt.mlx);
	free_scene(minirt.scene);
	mlx_delete_image(minirt.mlx, minirt.img);
	mlx_terminate(minirt.mlx);
	return (0);
}
