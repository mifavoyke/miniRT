/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_intersections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zuzanapiarova <zuzanapiarova@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 12:03:06 by zpiarova          #+#    #+#             */
/*   Updated: 2025/05/13 10:21:18 by zuzanapiaro      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minirt.h"

void print_inter_list(t_inter **head)
{
	t_inter *temp;
	
	if (!head || !*head)
		return ;
	temp = *head;
	while (temp)
	{
		if (temp->type == SPHERE)
			printf("sphere %d ", temp->id);
		else if (temp->type == CYLINDER	)
			printf("cylinder %d ", temp->id);
		else if (temp->type == PLANE)
			printf("plane %d ", temp->id);
		printf("%f\n", temp->distance);
		temp = temp->next;
	}
	printf("-----------------\n");
}


// creates linked list of intersections of ray with all scene objects
// --> for one pixel, checks all objects in the scene
t_inter	*create_intersection_list(t_scene *scene, t_coord ray)
{
	t_sphere	*temp_sp;
	t_plane		*temp_pl;
	t_cylinder	*temp_cy;
	t_sphere	*temp_light_ball;
	t_inter		*head;
	t_inter		*new_node;

	head = NULL;
	new_node = NULL;
	temp_sp = scene->sp;
	temp_cy = scene->cy;
	temp_pl = scene->pl;
	temp_light_ball = scene->light_spheres;
	while (temp_sp)
	{
		new_node = find_sphere_inters(ray, scene->c.point, (void *)temp_sp);
		append_node(new_node, &head);
		temp_sp = temp_sp->next;
	}
	while (temp_light_ball)
	{
		new_node = find_sphere_inters(ray, scene->c.point, (void *)temp_light_ball);
		append_node(new_node, &head);
		temp_light_ball = temp_light_ball->next;
	}
	while (temp_cy)
	{
		new_node = find_cylinder_inters(ray, scene->c.point, (void *)temp_cy);
		append_node(new_node, &head);
		temp_cy = temp_cy->next;
	}
	while (temp_pl)
	{
		new_node = find_plane_inters(ray, scene->c.point, (void *)temp_pl);
		append_node(new_node, &head);
		temp_pl = temp_pl->next;
	}
	merge_sort(&head);
	// print_inter_list(&head);
	return (head);
}

// sets attributes to inter pointer
// color, id and type have to be set outside of func BECAUSE OF FCKING NORMINET
void	set_id_colour_type(t_inter *inter, int id, enum e_obj_t t, t_colour c)
{
	inter->id = id;
	inter->colour = c;
	inter->type = t;
}

// allocates intersection node and fills it with required data
// color, id and type have to be set outside of func BECAUSE OF FCKING NORMINET
t_inter	*make_inter(void *obj, float t, t_coord ray, t_coord origin)
{
	t_inter	*inter;

	inter = (t_inter *)malloc(sizeof(t_inter));
	if (!inter)
		return (NULL);
	inter->obj = obj;
	inter->distance = fabsf(t);
	inter->point = set_coord(
			origin.x + t * ray.x,
			origin.y + t * ray.y,
			origin.z + t * ray.z
			);
	inter->next = NULL;
	return (inter);
}

// returns intersection list for a specific object with one ray
t_inter	*return_object_inters(t_inter *in1, t_inter *in2)
{
	if (!in1 && !in2)
		return (NULL);
	if (in1)
	{
		append_node(in2, &in1);
		return (in1);
	}
	else if (in2)
		return (in2);
	return (NULL);
}