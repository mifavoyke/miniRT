/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_resize_functions.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpiarova <zpiarova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 15:43:00 by zpiarova          #+#    #+#             */
/*   Updated: 2025/05/15 16:42:56 by zpiarova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

// checks if mouse is clicked on any object, if yes, stores it for processing
// it checks if there is any intersection stored in the intersection array on
// position of the mouse click
void	set_object_to_resize(t_minirt *minirt, t_mouse *mouse)
{
	if (mouse->mousex >= 0 && mouse->mousex < WIDTH
		&& mouse->mousey >= 0 && mouse->mousey < HEIGHT
		&& minirt->intersection[mouse->mousey][mouse->mousex])
		mouse->object = minirt->intersection[mouse->mousey][mouse->mousex];
	else
		mouse->object = NULL;
}

// very simple algo to resize the sphere diameter based on drag movement
void	resize_sphere(t_sphere *sp, int deltax, int deltay)
{
	float	new_d;

	if (abs(deltax) >= abs(deltay))
		new_d = sp->diameter + deltax / RESIZE_CONST;
	else
		new_d = sp->diameter - deltay / RESIZE_CONST;
	if (new_d > 1)
		sp->diameter = new_d;
	else
		sp->diameter = 1;
}

// very simple algo to change cylinder height/diameter based on drag movement
// if there is more prevalent horizontal change, change cylinder diameter
// if there is more prevalent vertical movement, change cylinder height
void	resize_cylinder(t_cylinder *cy, int deltax, int deltay)
{
	float	new_d;
	float	new_h;

	if (abs(deltax) >= abs(deltay))
	{
		new_d = cy->diameter + deltax / RESIZE_CONST;
		if (new_d > 0.5)
			cy->diameter = new_d;
		else
			cy->diameter = 0.5;
	}
	else
	{
		new_h = cy->h - deltay / RESIZE_CONST;
		if (new_h > 0.5)
			cy->h = new_h;
		else
			cy->h = 0.5;
	}
}

// processes drag mouse movement
// drag right - xdelta+ - increase diameter - cy,sp
// drag left - xdelta- - decrease diamerer - cy,sp
// drag up - ydelta+ - increase height - cy
// drag down - ydelta - decrease height - cy
void	resize_object(t_minirt *minirt, t_mouse *mouse)
{
	int32_t		deltax;
	int32_t		deltay;

	if (mouse->mousex < 0 || mouse->mousex >= WIDTH
		|| mouse->mousey < 0 || mouse->mousey >= HEIGHT
		|| mouse->new_mousex < 0 || mouse->new_mousex >= WIDTH
		|| mouse->new_mousey < 0 || mouse->new_mousey >= HEIGHT
		|| !mouse->object)
		return ;
	deltax = mouse->new_mousex - mouse->mousex;
	deltay = mouse->new_mousey - mouse->mousey;
	if (mouse->object->type == SPHERE)
		resize_sphere((t_sphere *)mouse->object->obj, deltax, deltay);
	if (mouse->object->type == CYLINDER)
		resize_cylinder((t_cylinder *)mouse->object->obj, deltax, deltay);
	if (generate_image(minirt) == ERROR)
	{
		cleanup(minirt);
		exit(ERROR);
	}
}
