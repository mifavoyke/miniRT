/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpiarova <zpiarova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 11:11:41 by zpiarova          #+#    #+#             */
/*   Updated: 2025/04/30 11:16:11 by zpiarova         ###   ########.fr       */
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
	tm = &(minirt->scene->Tm);
	cam->point.x += direction.x * translation;
	cam->point.y += direction.y * translation;
	cam->point.z += direction.z * translation;
	tm->Tr.x = cam->point.x;
	tm->Tr.y = cam->point.y;
	tm->Tr.z = cam->point.z;
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

	tm = &(minirt->scene->Tm);
	tm->F = rotate_vector_around_axis(tm->F, tm->R, angle);
	tm->U = rotate_vector_around_axis(tm->U, tm->R, angle);
	normalize(&tm->F);
	normalize(&tm->U);
	tm->R = get_cross_product(tm->F, tm->U);
	normalize(&tm->R);
	*original_vector = tm->F;
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
	tm = &(minirt->scene->Tm);
	tm->R = rotate_vector_around_axis(tm->R, tm->F, angle);
	tm->U = rotate_vector_around_axis(tm->U, tm->F, angle);
	normalize(&tm->R);
	normalize(&tm->U);
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

	tm = &(minirt->scene->Tm);
	tm->R = rotate_vector_around_axis(tm->R, tm->U, angle);
	tm->F = rotate_vector_around_axis(tm->F, tm->U, angle);
	normalize(&tm->R);
	normalize(&tm->F);
	tm->U = get_cross_product(tm->R, tm->F);
	normalize(&tm->U);
	*original_vector = tm->F;
	if (generate_image(minirt) == ERROR)
	{
		cleanup(minirt);
		exit(ERROR);
	}
}
