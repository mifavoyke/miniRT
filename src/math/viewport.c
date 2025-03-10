/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viewport.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpiarova <zpiarova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 20:53:45 by zpiarova          #+#    #+#             */
/*   Updated: 2025/03/10 21:03:18 by zpiarova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

// calculates the distance of the camera from the viewport plane (representing screen)
float get_viewport_width(float angle_deg, float distance)
{
	float   viewport_width;
	float   angle_rad;
	
	// Convert angle to radians
	angle_rad = angle_deg / 2 * M_PI / 180.0;
	viewport_width = 2 * (tan(angle_rad) / distance);
	return (viewport_width);
}

// it is calculated based on viewport width and to keep the ratio of screen width:height
float get_viewport_height(float viewport_width)
{
	return (viewport_width * HEIGHT / WIDTH);
}

// sets the information we have abot the viewport plane - must be regenerated for each new render/movement
void set_viewport_plane(t_scene *scene, t_viewport *v)
{
	float d = 1.0; // TODO: maybe the distance d must be calculated, for now it is 1, coming from normalized vector 
	
	v->viewport_width = get_viewport_width(60.0, d); 
	v->viewport_height = get_viewport_height(v->viewport_width);
	v->viewport_centre = get_point_on_vector(scene->c.viewpoint, scene->c.vector, d);
	v->corner_distance = sqrt(pow(v->viewport_width / 2, 2) + pow(v->viewport_height / 2, 2));
	get_viewport_corners(scene->viewport, scene->c);
    printf("viewport:\nWIDTH: %f, HEIGHT: %f | S [%f, %f, %f] | corner distance %f \n\tVtr[%f, %f, %f]\n\tVtl[%f, %f, %f]\n\tVbl[%f, %f, %f]\n\tVbr[%f, %f, %f]\n\t", 
            v->viewport_width, v->viewport_height, v->viewport_centre.x, v->viewport_centre.y, v->viewport_centre.z, v->corner_distance, 
            v->Vtr.x, v->Vtr.y, v->Vtr.z, v->Vtl.x, v->Vtl.y, v->Vtl.z, v->Vbl.x, v->Vbl.y, v->Vbl.z, v->Vbr.x, v->Vbr.y, v->Vbr.z);
}