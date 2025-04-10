/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhusieva <yhusieva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 14:13:05 by zpiarova          #+#    #+#             */
/*   Updated: 2025/03/28 16:36:21 by yhusieva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void move(t_minirt *minirt, char *msg, float *coord, int arithmetic)
{
    if (arithmetic == 0)
        *coord -= TRANSLATION;
    if (arithmetic == 1)
        *coord += TRANSLATION;
    printf("%s: ", msg);
    print_coord(minirt->scene->c.point);
    generate_image(minirt);
}

void redirect(t_minirt *minirt, char *msg, float *coord, int arithmetic)
{
    if (arithmetic == 0)
        *coord -= TRANSLATION_NORM;
    if (arithmetic == 1)
        *coord += TRANSLATION_NORM;
    normalize(&minirt->scene->c.vector);
    printf("%s:                         ", msg);
    print_coord(minirt->scene->c.vector);
    generate_image(minirt);
}

// bool mlx_is_mouse_down(mlx_t* mlx, mouse_key_t key);

void ft_hook(void *param)
{
    t_minirt *minirt;

    minirt = param;
    if (mlx_is_key_down(minirt->mlx, MLX_KEY_ESCAPE))
        mlx_close_window(minirt->mlx);
    // changes position of the camera
    if (mlx_is_key_down(minirt->mlx, MLX_KEY_D))
        move(minirt, "+x", &minirt->scene->c.point.x, 1);
    if (mlx_is_key_down(minirt->mlx, MLX_KEY_A))
        move(minirt, "-x", &minirt->scene->c.point.x, 0);
    if (mlx_is_key_down(minirt->mlx, MLX_KEY_M))
        move(minirt, "+y", &minirt->scene->c.point.y, 1);
    if (mlx_is_key_down(minirt->mlx, MLX_KEY_N))
        move(minirt, "-y", &minirt->scene->c.point.y, 0);
    if (mlx_is_key_down(minirt->mlx, MLX_KEY_W))
        move(minirt, "+z", &minirt->scene->c.point.z, 1);
    if (mlx_is_key_down(minirt->mlx, MLX_KEY_S))
        move(minirt, "-z", &minirt->scene->c.point.z, 0);
    // DIRECTIONAL VECTOR
    if (mlx_is_key_down(minirt->mlx, MLX_KEY_RIGHT))
        redirect(minirt, "+x", &minirt->scene->c.vector.x, 1);
    if (mlx_is_key_down(minirt->mlx, MLX_KEY_LEFT))
        redirect(minirt, "-x", &minirt->scene->c.vector.x, 0);
    if (mlx_is_key_down(minirt->mlx, MLX_KEY_K))
        redirect(minirt, "+y", &minirt->scene->c.vector.y, 1); // i dont understand what it changes but somehow it does
    if (mlx_is_key_down(minirt->mlx, MLX_KEY_J))
        redirect(minirt, "-y", &minirt->scene->c.vector.y, 0);
    if (mlx_is_key_down(minirt->mlx, MLX_KEY_UP))
        redirect(minirt, "+z", &minirt->scene->c.vector.z, 1);
    if (mlx_is_key_down(minirt->mlx, MLX_KEY_DOWN))
        redirect(minirt, "-z", &minirt->scene->c.vector.z, 0);
    // moving objs
    
}
