/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpiarova <zpiarova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 16:37:45 by yhusieva          #+#    #+#             */
/*   Updated: 2025/03/11 21:33:53 by zpiarova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void draw_line(mlx_image_t *image)
{
	int i = 0;

	while (i < 50)
	{
		mlx_put_pixel(image, transform_to_tl('x', (float)i), transform_to_tl('y', 0), 0xe5f89f);
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
	{
		ft_error_mlx();
		return (1);
	}
	minirt->img = mlx_new_image(minirt->mlx, minirt->img_width, minirt->img_height);
	if (!minirt->img || (mlx_image_to_window(minirt->mlx, minirt->img, 0, 0) < 0))
	{
		ft_error_mlx();
		return (1);
	}
	return (0);
}

int32_t main(int argc, char *argv[])
{
	t_minirt minirt;
	t_scene scene; // TEMPORARY SCENE WITH DEFAULT VALUES, YOU CAN HOOK IT UP TO HAVE VALUES FROM .rt FILES

	(void)argv;
	scene.c.vector.x = 0.707;
	scene.c.vector.y = 0.707;
	scene.c.vector.z = 0.0;
	scene.c.view_degree = 70.0;
	scene.c.viewpoint.x = -10.0;
	scene.c.viewpoint.y = 0;
	scene.c.viewpoint.z = 1;
	scene.sp = (t_sphere *)malloc(sizeof(t_sphere *));
	scene.sp->centre.x = 0;
	scene.sp->centre.y = 50;
	scene.sp->centre.z = 0;
	scene.sp->colour.r = 64;
	scene.sp->colour.g = 224;
	scene.sp->colour.b = 208;
	scene.sp->diameter = 10.0;
	scene.sp->next = NULL;

	if (argc != 2)
	{
		printf("Error\nDon't: ./miniRT\nDo: ./miniRT [scene].rt\n");
		return (1);
	}
	if (check_file_format(argv[1]))
	{
		printf("Wrong scene format.\n");
		return (1);
	}
	if (minirt_init(&minirt))
		return (1); // how will we handle errors? should we exit but what about the window termination?
	if (!parse_scene(&minirt, argv[1]))
	{
		// here will probably connect to my part right ? -Zuzana (for now i use it to check output of math functions)
		draw_line(minirt.img);
		set_viewport_plane(&scene);
		shoot_rays(&scene);
	}
	else
		return (1); // if you terminate the window it seg faults
	mlx_loop_hook(minirt.mlx, ft_hook, (void *)&minirt);
	mlx_loop(minirt.mlx);
	free(scene.sp);
	mlx_terminate(minirt.mlx);
	return (0);
}