/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhusieva <yhusieva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 14:13:05 by zpiarova          #+#    #+#             */
/*   Updated: 2025/04/21 12:40:54 by yhusieva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"
#define ANGLE_RADIAN 0.2
#define ZOOM 0.5
#define TRANSLATION 5

// Euclidean space vs Cartesian

void move(t_minirt *minirt, float *coord, float translation)
{
    *coord += translation;
    print_coord(minirt->scene->c.point);
    generate_image(minirt);
}

// Rotates up and down. Rotation matrix:
// Rx = | 1    0        0     |
//      | 0  cos(a)  -sin(a)  |
//      | 0  sin(a)   cos(a)  |
void rotate_x(t_minirt *minirt, t_coord *original_vector, double angle)
{
    t_coord new_vector;

    new_vector.x = original_vector->x;
    new_vector.y = cos(angle) * original_vector->y - sin(angle) * original_vector->z;
    new_vector.z = sin(angle) * original_vector->y + cos(angle) * original_vector->z;
    normalize(&new_vector);
    print_coord(new_vector);
    *original_vector = new_vector;
    generate_image(minirt);
}

// Rotates in spiral - yaw. Rotation matrix:
// Ry = | cos(a)   0   sin(a) |
//      |   0      1     0    |
//      | -sin(a)  0   cos(a) |
void rotate_y(t_minirt *minirt, t_coord *original_vector, double angle)
{
    t_coord new_vector;

    new_vector.x = cos(angle) * original_vector->x + sin(angle) * original_vector->z;
    new_vector.y = original_vector->y;
    new_vector.z = -sin(angle) * original_vector->x + cos(angle) * original_vector->z;
    normalize(&new_vector);
    print_coord(new_vector);
    *original_vector = new_vector;
    generate_image(minirt);
}

// Rotates left and right. Rotation matrix:
// Rz = | cos(a)  -sin(a)  0 |
//      | sin(a)   cos(a)  0 |
//      |   0        0     1 |
void rotate_z(t_minirt *minirt, t_coord *original_vector, double angle)
{
    t_coord new_vector;

    new_vector.x = cos(angle) * original_vector->x - sin(angle) * original_vector->y;
    new_vector.y = sin(angle) * original_vector->x + cos(angle) * original_vector->y;
    new_vector.z = original_vector->z;
    normalize(&new_vector);
    print_coord(new_vector);
    *original_vector = new_vector;
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
        move(minirt, &minirt->scene->c.point.x, TRANSLATION);
    if (mlx_is_key_down(minirt->mlx, MLX_KEY_A))
        move(minirt, &minirt->scene->c.point.x, -TRANSLATION);
    if (mlx_is_key_down(minirt->mlx, MLX_KEY_W))
        move(minirt, &minirt->scene->c.point.z, TRANSLATION);
    if (mlx_is_key_down(minirt->mlx, MLX_KEY_S))
        move(minirt, &minirt->scene->c.point.z, -TRANSLATION);
    // DIRECTIONAL VECTOR
    if (mlx_is_key_down(minirt->mlx, MLX_KEY_UP))
        rotate_x(minirt, &minirt->scene->c.vector, ANGLE_RADIAN);
    if (mlx_is_key_down(minirt->mlx, MLX_KEY_DOWN))
        rotate_x(minirt, &minirt->scene->c.vector, -ANGLE_RADIAN);
    if (mlx_is_key_down(minirt->mlx, MLX_KEY_K))
        rotate_y(minirt, &minirt->scene->c.vector, ANGLE_RADIAN);
    if (mlx_is_key_down(minirt->mlx, MLX_KEY_J))
        rotate_y(minirt, &minirt->scene->c.vector, -ANGLE_RADIAN);
    if (mlx_is_key_down(minirt->mlx, MLX_KEY_LEFT))
        rotate_z(minirt, &minirt->scene->c.vector, ANGLE_RADIAN);
    if (mlx_is_key_down(minirt->mlx, MLX_KEY_RIGHT))
        rotate_z(minirt, &minirt->scene->c.vector, -ANGLE_RADIAN);
    // moving objs
}

void scroll_zoom(double xdelta, double ydelta, void *param)
{
    t_minirt *minirt;
    (void)xdelta; // what is it for?

    minirt = (t_minirt *)param;
    if (ydelta > 0)
        move(minirt, &minirt->scene->c.point.y, ZOOM);
    else if (ydelta < 0)
        move(minirt, &minirt->scene->c.point.y, -ZOOM);
}
