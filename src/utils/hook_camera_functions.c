/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_camera_functions.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpiarova <zpiarova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 11:11:41 by zpiarova          #+#    #+#             */
/*   Updated: 2025/05/15 16:32:12 by zpiarova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

// moves camera point relative to local axis, not relative to the world axis 
// axis to move along is specified by direction - local forward/up/right vector
// updates both camera and the transformation matrix Tr component accordingly
void	move(t_minirt *minirt, t_coord direction, float translation)
{
	t_camera	*cam;
	t_matrix	*tm;

	cam = &(minirt->scene->c);
	tm = &(minirt->scene->tm);
	cam->point.x += direction.x * translation;
	cam->point.y += direction.y * translation;
	cam->point.z += direction.z * translation;
	tm->translation.x = cam->point.x;
	tm->translation.y = cam->point.y;
	tm->translation.z = cam->point.z;
	if (generate_image(minirt) == ERROR)
	{
		cleanup(minirt);
		exit(ERROR);
	}
}

// rotates along camera's local x(R) axis (1,0,0) - PITCH (moves up and down)
// R vector from transformation matrix is unchanged, rotate F and U along it
// update the stored camera otientation vector to be the new F
void	rotate_x(t_minirt *minirt, t_coord *original_vector, float angle)
{
	t_matrix	*tm;

	tm = &(minirt->scene->tm);
	tm->forward = rotate_vector_around_axis(tm->forward, tm->right, angle);
	tm->up = rotate_vector_around_axis(tm->up, tm->right, angle);
	normalize(&tm->forward);
	normalize(&tm->up);
	tm->right = cross(tm->forward, tm->up);
	normalize(&tm->right);
	*original_vector = tm->forward;
	if (generate_image(minirt) == ERROR)
	{
		cleanup(minirt);
		exit(ERROR);
	}
}

// rotates along camera's local y(F) axis (0,1,0) - ROLL (shoulder to shoulder)
// F vector from transformation matrix is unchanged, rotate R and U along it
// the stored camera otientation vector is unchanged as we did not rotate it
// since we rotated around it
void	rotate_y(t_minirt *minirt, t_coord *original_vector, float angle)
{
	t_matrix	*tm;

	(void)original_vector;
	tm = &(minirt->scene->tm);
	tm->right = rotate_vector_around_axis(tm->right, tm->forward, angle);
	tm->up = rotate_vector_around_axis(tm->up, tm->forward, angle);
	normalize(&tm->right);
	normalize(&tm->up);
	if (generate_image(minirt) == ERROR)
	{
		cleanup(minirt);
		exit(ERROR);
	}
}

// rotates along camera's local z(U) axis (0,0,1) - YAW (moves side to side)
// U vector from transformation matrix is unchanged, rotate F and R along it
// update the stored camera otientation vector to be the new F
void	rotate_z(t_minirt *minirt, t_coord *original_vector, float angle)
{
	t_matrix	*tm;

	tm = &(minirt->scene->tm);
	tm->right = rotate_vector_around_axis(tm->right, tm->up, angle);
	tm->forward = rotate_vector_around_axis(tm->forward, tm->up, angle);
	normalize(&tm->right);
	normalize(&tm->forward);
	tm->up = cross(tm->right, tm->forward);
	normalize(&tm->up);
	*original_vector = tm->forward;
	if (generate_image(minirt) == ERROR)
	{
		cleanup(minirt);
		exit(ERROR);
	}
}
