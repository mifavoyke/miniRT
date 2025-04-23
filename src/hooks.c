/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhusieva <yhusieva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 14:13:05 by zpiarova          #+#    #+#             */
/*   Updated: 2025/04/23 19:41:30 by yhusieva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void move(t_minirt *minirt, float *coord, float translation)
{
    *coord += translation;
    print_coord(minirt->scene->c.point);
    free_inter(minirt->intersection, minirt->img_height, minirt->img_width);
    if (generate_image(minirt))
        exit(1);
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
    free_inter(minirt->intersection, minirt->img_height, minirt->img_width);
    if (generate_image(minirt))
        exit(1);
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
    free_inter(minirt->intersection, minirt->img_height, minirt->img_width);
    if (generate_image(minirt))
        exit(1);
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
    free_inter(minirt->intersection, minirt->img_height, minirt->img_width);
    if (generate_image(minirt))
        exit(1);
}

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

void resize_hook(int width, int height, void *param)
{
    t_minirt *minirt;

    minirt = (t_minirt *)param;
    mlx_resize_image(minirt->img, width, height);
    free_inter(minirt->intersection, minirt->img_height, minirt->img_width);
    free_pixels(minirt->pixels, minirt->img_height);
    minirt->img_width = width;
    minirt->img_height = height;
    if (generate_image(minirt))
        exit(1);
    // mlx_image_to_window(minirt->mlx, minirt->img, 0, 0);
}
