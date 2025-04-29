/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zuzanapiarova <zuzanapiarova@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 14:13:05 by zpiarova          #+#    #+#             */
/*   Updated: 2025/04/29 23:04:34 by zuzanapiaro      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

// update the stored transformation matrix
// and update the stored camera position cam->point
// Tr = | 0   0   0  Tx | - [ Rx  Fx  Ux  *Tx ]
//      | 0   0   0  Ty | - [ Ry  Fy  Uy  *Ty ]
//      | 0   0   0  Tz | - [ Rz  Fz  Uz  *Tz ]
//      | 0   0   0   1 | - [  0   0   0    1 ]
// the elements with * are the ones to be updated by the rotation
// void move(t_minirt *minirt, float *coord, float translation)
// {
//     *coord += translation;
//     minirt->scene->Tm = find_transformation_matrix(minirt->scene->c);
//     print_coord(minirt->scene->c.point);
//     if (generate_image(minirt) == ERROR)
//     {
//         cleanup(minirt);
//         exit(ERROR);
//     }
// }

// this moves camera relative to its local axis, not relative to the world axis 
// direction is the direction of movement in local camera space - forward, up, or right
void move(t_minirt *minirt, t_coord direction, float translation)
{
    t_camera *cam;
    t_matrix *Tm;

    cam = &(minirt->scene->c);
    Tm = &(minirt->scene->Tm);
    cam->point.x += direction.x * translation;
    cam->point.y += direction.y * translation;
    cam->point.z += direction.z * translation;
    // ✅ Rebuild the transformation matrix
    Tm->Tr.x = cam->point.x;
    Tm->Tr.y = cam->point.y;
    Tm->Tr.z = cam->point.z;
    // Re-render
    if (generate_image(minirt) == ERROR)
    {
        cleanup(minirt);
        exit(ERROR);
    }
}

// I have a camera positioned in 3D space and oriented by a transformation matrix from
// a default position (0, 0, 0) and default forward vector (0, 1, 0)

// Rotate a vector `v` around `axis` by `angle` radians - Rodriguez's formula
t_coord rotate_vector_around_axis(t_coord v, t_coord axis, float angle)
{
    t_coord result;
    float c = cosf(angle);
    float s = -sinf(angle); // set to minus as in left-handed system the forwrd vector is minus the cross product of right x up

    // Normalize the axis
    normalize(&axis);
    // Rodrigues' rotation formula
    result.x = v.x * c + (1 - c) * (axis.x * (axis.x * v.x + axis.y * v.y + axis.z * v.z)) + s * (axis.y * v.z - axis.z * v.y);
    result.y = v.y * c + (1 - c) * (axis.y * (axis.x * v.x + axis.y * v.y + axis.z * v.z)) + s * (axis.z * v.x - axis.x * v.z);
    result.z = v.z * c + (1 - c) * (axis.z * (axis.x * v.x + axis.y * v.y + axis.z * v.z)) + s * (axis.x * v.y - axis.y * v.x);

    return (result);
}

// !!!!!!!!!!!!!!!!!!!!
// n most cases, no, you do not need to explicitly normalize the camera's
// orientation vectors after applying the rotation matrices, because rotation
// matrices are orthogonal. This means that, after applying a rotation matrix,
// the basis vectors (right, forward, up) are guaranteed to remain normalized
// if they were initially normalized.

// Rotates up and down - pitch. Rotation matrix:
// Rx = | 1    0        0     0 | - [ Rx   Fx   Ux  Tx ]
//      | 0  cos(a)  -sin(a)  0 | - [ Ry  *Fy  *Uy  Ty ]
//      | 0  sin(a)   cos(a)  0 | - [ Rz  *Fz  *Uz  Tz ]
//      | 0    0        0     1 | - [ 0    0    0    1 ]
// the elements with * are the ones to be updated by the rotation
// we apply these rotations to the existing transformation matrix - up and forward axis
// and update the stored camera otientation vector
void rotate_x(t_minirt *minirt, t_coord *original_vector, float angle)
{
    t_matrix *Tm;
    
    Tm = &(minirt->scene->Tm);
    Tm->F = rotate_vector_around_axis(Tm->F, Tm->R, angle);
    Tm->U = rotate_vector_around_axis(Tm->U, Tm->R, angle);
    normalize(&Tm->F);
    normalize(&Tm->U);
    Tm->R = get_cross_product(Tm->F, Tm->U);
    normalize(&Tm->R);
    *original_vector = Tm->F;
    if (generate_image(minirt) == ERROR)
    {
        cleanup(minirt);
        exit(ERROR);
    }
}

// Rotates in spiral (tilt head shoulder to shoulder) - roll. Rotation matrix:
// Ry = | cos(a)   0   sin(a)  0 | - [ *Rx  Fx  *Ux  Tx ]
//      |   0      1     0     0 | - [  Ry  Fy   Uy  Ty ]
//      | -sin(a)  0   cos(a)  0 | - [ *Rz  Fz  *Uz  Tz ]
//      |   0      0     0     1 | - [ 0    0    0    1 ]
// the elements with * are the ones to be updated by the rotation
// we apply these rotations to the existing transformation matrix - right and up axis
// and update the stored camera otientation vector
void rotate_y(t_minirt *minirt, t_coord *original_vector, float angle)
{
    t_matrix *Tm;
    
    Tm = &(minirt->scene->Tm);
    Tm->R = rotate_vector_around_axis(Tm->R, Tm->F, angle);
    Tm->U = rotate_vector_around_axis(Tm->U, Tm->F, angle);
    normalize(&Tm->R);
    normalize(&Tm->U);
    Tm->F = get_cross_product(Tm->R, Tm->U);
    normalize(&Tm->F);
    *original_vector = Tm->F;
    if (generate_image(minirt) == ERROR)
    {
        cleanup(minirt);
        exit(ERROR);
    }
}

// Rotates left and right - yaw. Rotation matrix:
// Rz = | cos(a)  -sin(a)  0   0 | - [ *Rx  *Fx  Ux  Tx ]
//      | sin(a)   cos(a)  0   0 | - [ *Ry  *Fy  Uy  Ty ]
//      |   0        0     1   0 | - [  Rz   Fz  Uz  Tz ]
//      |   0        0     0   1 | - [ 0    0    0    1 ]
// the elements with * are the ones to be updated by the rotation
// we apply these rotations to the existing transformation matrix - right and forward axis
// and update the stored camera otientation vector
void rotate_z(t_minirt *minirt, t_coord *original_vector, float angle)
{
    t_matrix *Tm;
    
    Tm = &(minirt->scene->Tm);
    Tm->R = rotate_vector_around_axis(Tm->R, Tm->U, angle);
    Tm->F = rotate_vector_around_axis(Tm->F, Tm->U, angle);
    normalize(&Tm->R);
    normalize(&Tm->F);
    Tm->U = get_cross_product(Tm->R, Tm->F);
    normalize(&Tm->U);
    *original_vector = Tm->F;
    if (generate_image(minirt) == ERROR)
    {
        cleanup(minirt);
        exit(ERROR);
    }
}

void ft_hook(void *param)
{
    t_minirt *minirt;

    minirt = param;
    if (mlx_is_key_down(minirt->mlx, MLX_KEY_ESCAPE))
        mlx_close_window(minirt->mlx);
    // changes position of the camera
    if (mlx_is_key_down(minirt->mlx, MLX_KEY_D))
        move(minirt, minirt->scene->Tm.R, TRANSLATION);
    if (mlx_is_key_down(minirt->mlx, MLX_KEY_A))
        move(minirt, minirt->scene->Tm.R, -TRANSLATION);
    if (mlx_is_key_down(minirt->mlx, MLX_KEY_W))
        move(minirt, minirt->scene->Tm.U, TRANSLATION);
    if (mlx_is_key_down(minirt->mlx, MLX_KEY_S))
        move(minirt, minirt->scene->Tm.U, -TRANSLATION);
    // if (mlx_is_key_down(minirt->mlx, MLX_KEY_D))
    //     move(minirt, &minirt->scene->c.point.x, TRANSLATION);
    // if (mlx_is_key_down(minirt->mlx, MLX_KEY_A))
    //     move(minirt, &minirt->scene->c.point.x, -TRANSLATION);
    // if (mlx_is_key_down(minirt->mlx, MLX_KEY_W))
    //     move(minirt, &minirt->scene->c.point.z, TRANSLATION);
    // if (mlx_is_key_down(minirt->mlx, MLX_KEY_S))
    //     move(minirt, &minirt->scene->c.point.z, -TRANSLATION);
    // DIRECTIONAL VECTOR
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

void scroll_zoom(double xdelta, double ydelta, void *param)
{
    t_minirt *minirt;
    (void)xdelta; // what is it for?

    minirt = (t_minirt *)param;
    if (ydelta > 0)
        move(minirt, minirt->scene->Tm.F, ZOOM);
    else if (ydelta < 0)
        move(minirt, minirt->scene->Tm.F, -ZOOM);
}

void resize_hook(int width, int height, void *param)
{
    t_minirt *minirt;

    minirt = (t_minirt *)param;
    free_pixels(minirt->pixels, minirt->img_height);
    free_inter(minirt->intersection, minirt->img_height, minirt->img_width);
    minirt->img_width = width;
    minirt->img_height = height;
    minirt->pixels = allocate_pixels(minirt->img_width, minirt->img_height, minirt->scene->background);
	if (!minirt->pixels)
    {
        cleanup(minirt);
        exit(ERROR);
    }
    minirt->intersection = allocate_inter(minirt->img_width, minirt->img_height);
    if (!minirt->intersection)
    {
        cleanup(minirt);
        exit(ERROR);
    }
    mlx_resize_image(minirt->img, width, height);
    if (generate_image(minirt) == ERROR)
    {
        cleanup(minirt);
        exit(ERROR);
    }
}
