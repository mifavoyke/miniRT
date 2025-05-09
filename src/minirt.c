/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhusieva <yhusieva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 14:13:15 by zpiarova          #+#    #+#             */
/*   Updated: 2025/05/09 17:06:42 by yhusieva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	cleanup(t_minirt *minirt)
{
	free_pixels(minirt->pixels, minirt->img_height);
	free_inter(minirt->intersection, minirt->img_height, minirt->img_width);
	free_scene(minirt->scene);
	mlx_delete_image(minirt->mlx, minirt->img);
	mlx_terminate(minirt->mlx);
}

// iterate over 2Dpixels array and render color stored for each pixel to screen
static void	render_pixels(t_minirt *minirt)
{
	int			x;
	int			y;
	t_colour	c;

	y = -1;
	while (++y < minirt->img_height)
	{
		x = -1;
		while (++x < minirt->img_width)
		{
			c = minirt->pixels[y][x];
			mlx_put_pixel(minirt->img, x, y, ft_pixel(c.r, c.g, c.b, c.a));
		}
	}
}

int	generate_image(t_minirt *minirt)
{
	shoot_rays(minirt, minirt->scene);
	lighting(minirt);
	render_pixels(minirt);
	return (SUCCESS);
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
	if (generate_image(&minirt) == ERROR)
		return (ERROR);
	mlx_loop_hook(minirt.mlx, ft_hook, (void *)&minirt);
	mlx_scroll_hook(minirt.mlx, &scroll_zoom, (void *)&minirt);
	mlx_resize_hook(minirt.mlx, resize_hook, (void *)&minirt);
	mlx_loop(minirt.mlx);
	cleanup(&minirt);
	return (SUCCESS);
}
