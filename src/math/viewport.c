/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viewport.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpiarova <zpiarova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 20:53:45 by zpiarova          #+#    #+#             */
/*   Updated: 2025/04/17 19:45:26 by zpiarova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

// calculates width of the viewport plane (representing screen) in the 3d space
// float get_viewport_width(float angle_deg, float distance)
// {
// 	float   viewport_width;
// 	float   angle_rad;

// 	// Convert angle to radians
// 	angle_rad = angle_deg * M_PI / 180.0;
// 	viewport_width = 2 * (tan(angle_rad / 2) * distance); // 
// 	return (viewport_width);
// }

// // calculates height of the viewport plane (representing screen) based on viewport width
// // keeps the width:height ratio of screen 
// float get_viewport_height(t_minirt *minirt, float viewport_width)
// {
// 	(void)minirt;
// 	return (viewport_width * HEIGHT / WIDTH);
// }

// // sets the information we have abot the viewport plane - must be regenerated for each new render/movement
// t_viewport *set_viewport_plane(t_minirt *minirt, t_scene scene)
// {
// 	t_viewport *v;

// 	v = (t_viewport *)malloc(sizeof(t_viewport));
// 	v->d = 1.0;
// 	v->viewport_width = get_viewport_width(scene.c.view_degree, v->d);
// 	v->viewport_height = get_viewport_height(minirt, v->viewport_width);
// 	return (v);
// }
