/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpiarova <zpiarova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 17:06:55 by zpiarova          #+#    #+#             */
/*   Updated: 2025/03/11 17:07:14 by zpiarova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"


// mapping screen pixel coordinate to a coordinate in the scene, mapped to the viewport size
// x and y are coordinates on the screen
// TODO: not workng properly, check some vector math t understand better 
void get_viewport_corners(t_viewport *v, t_camera c)
{
	t_coord temp_vector;
	t_coord normal;

	// we have lengths, angles, coordinates of S(viewport_centre) and C(camera.viewpoint), and CS vector(camera.vector), and it is right-angled at S
	// find perpendicular vector
		// Choose any arbitrary vector t that is not parallel to →CS - simple choice is (1, 0, 0), (0,1,0), (0,0,1)
		temp_vector.x = 1;
		temp_vector.y = 0;
		temp_vector.z = 0;
		// but if it happend to be collinear with CS, pick another one of them 
		if (are_collinear(c.vector, temp_vector))
		{
			temp_vector.x = 0;
			temp_vector.y = 1;
			temp_vector.z = 0;
		}
		// compute the cross product: 𝑁 = →CS × t --> this gives perpendicular vector N
		normal = get_cross_product(c.vector, temp_vector);
		// normalize N to get a unit vector: N(normalized) = N / |N|
		normalize(&normal);
	// compute third point C(Vtl, Vtr, Vbl, Vbr) --> 𝐶 = S + |SV|(corner_distance) * N(normalized) --> expand for coordinates x, y, z
	v->Vtr.x = v->viewport_centre.x + v->corner_center_distance * normal.x;
	v->Vtr.y = v->viewport_centre.y + v->corner_center_distance * normal.y;
	v->Vtr.z = v->viewport_centre.z + v->corner_center_distance * normal.z;
	//printf("|Vtr| = %f, Vtr [%f, %f, %f]\n", v->corner_distance, v->Vtr.x, v->Vtr.y, v->Vtr.z);
	
	// Vtl = ;
	// Vbl = ;
	// Vbr = ;
}