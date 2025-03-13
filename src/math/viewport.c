/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viewport.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpiarova <zpiarova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 20:53:45 by zpiarova          #+#    #+#             */
/*   Updated: 2025/03/13 10:24:12 by zpiarova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

// calculates the distance of the camera from the viewport plane (representing screen)
float get_viewport_width(float angle_deg, float distance)
{
	float   viewport_width;
	float   angle_rad;

	// Convert angle to radians
	angle_rad = angle_deg * M_PI / 180.0;
	viewport_width = 2 * (tan(angle_rad / 2) * distance);
	return (viewport_width);
}

// it is calculated based on viewport width and to keep the ratio of screen width:height
float get_viewport_height(float viewport_width)
{
	return (viewport_width * HEIGHT / WIDTH);
}

// sets the information we have abot the viewport plane - must be regenerated for each new render/movement
t_viewport *set_viewport_plane(t_scene scene)
{
	t_viewport *v;

	v = (t_viewport *)malloc(sizeof(t_viewport));
	v->d = 1.0;
	v->viewport_width = get_viewport_width(scene.c.view_degree, v->d);
	v->viewport_height = get_viewport_height(v->viewport_width);
	v->viewport_centre = get_point_on_vector(scene.c.viewpoint, scene.c.vector, v->d);
    printf("viewport:\nWIDTH: %f, HEIGHT: %f | C[%f, %f, %f] v(%f, %f, %f) S [%f, %f, %f] | v normalized: %d\n",
            v->viewport_width, v->viewport_height, scene.c.viewpoint.x, scene.c.viewpoint.y, scene.c.viewpoint.z, 
			scene.c.vector.x, scene.c.vector.y, scene.c.vector.z,
			v->viewport_centre.x, v->viewport_centre.y, v->viewport_centre.z, is_vector_normalized(scene.c.vector));
	return (v);
}
