/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpiarova <zpiarova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 14:13:05 by zpiarova          #+#    #+#             */
/*   Updated: 2025/04/30 11:14:12 by zpiarova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

// moves camera forward on zoom relative to its local forward axis
void	scroll_zoom(double xdelta, double ydelta, void *param)
{
	t_minirt	*minirt;

	(void)xdelta;
	minirt = (t_minirt *)param;
	if (ydelta > 0)
		move(minirt, minirt->scene->Tm.F, ZOOM);
	else if (ydelta < 0)
		move(minirt, minirt->scene->Tm.F, -ZOOM);
}

// hooks keys to control the program to relevant functions
void	ft_hook(void *param)
{
	t_minirt	*minirt;

	minirt = param;
	if (mlx_is_key_down(minirt->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(minirt->mlx);
	if (mlx_is_key_down(minirt->mlx, MLX_KEY_D))
		move(minirt, minirt->scene->Tm.R, TRANSLATION);
	if (mlx_is_key_down(minirt->mlx, MLX_KEY_A))
		move(minirt, minirt->scene->Tm.R, -TRANSLATION);
	if (mlx_is_key_down(minirt->mlx, MLX_KEY_W))
		move(minirt, minirt->scene->Tm.U, TRANSLATION);
	if (mlx_is_key_down(minirt->mlx, MLX_KEY_S))
		move(minirt, minirt->scene->Tm.U, -TRANSLATION);
	if (mlx_is_key_down(minirt->mlx, MLX_KEY_UP))
		rotate_x(minirt, &minirt->scene->c.vector, -ANGLE_RADIAN);
	if (mlx_is_key_down(minirt->mlx, MLX_KEY_DOWN))
		rotate_x(minirt, &minirt->scene->c.vector, ANGLE_RADIAN);
	if (mlx_is_key_down(minirt->mlx, MLX_KEY_K))
		rotate_y(minirt, &minirt->scene->c.vector, -ANGLE_RADIAN);
	if (mlx_is_key_down(minirt->mlx, MLX_KEY_J))
		rotate_y(minirt, &minirt->scene->c.vector, ANGLE_RADIAN);
	if (mlx_is_key_down(minirt->mlx, MLX_KEY_LEFT))
		rotate_z(minirt, &minirt->scene->c.vector, -ANGLE_RADIAN);
	if (mlx_is_key_down(minirt->mlx, MLX_KEY_RIGHT))
		rotate_z(minirt, &minirt->scene->c.vector, ANGLE_RADIAN);
}

// resizing the window reallocates allocated arrays:
// 1. array used to stored pixel information
// 2. array to store each ray's intersection list
void	resize_hook(int width, int height, void *param)
{
	t_minirt	*rt;

	rt = (t_minirt *)param;
	free_pixels(rt->pixels, rt->img_height);
	free_inter(rt->intersection, rt->img_height, rt->img_width);
	rt->img_width = width;
	rt->img_height = height;
	rt->pixels = allocate_pixels(rt->img_width, rt->img_height, rt->scene->bg);
	if (!rt->pixels)
	{
		cleanup(rt);
		exit(ERROR);
	}
	rt->intersection = allocate_inter(rt->img_width, rt->img_height);
	if (!rt->intersection)
	{
		cleanup(rt);
		exit(ERROR);
	}
	mlx_resize_image(rt->img, width, height);
	if (generate_image(rt) == ERROR)
	{
		cleanup(rt);
		exit(ERROR);
	}
}
