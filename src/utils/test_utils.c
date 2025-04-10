/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhusieva <yhusieva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 14:13:22 by zpiarova          #+#    #+#             */
/*   Updated: 2025/04/03 16:27:26 by yhusieva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static void print_colour(t_colour colour)
{
	printf("(%d, %d, %d)", colour.r, colour.g, colour.b);
}

void print_coord(t_coord coord)
{
	printf("(%.2f, %.2f, %.2f)\n", coord.x, coord.y, coord.z);
}

static void print_spheres(t_sphere *sp)
{
	t_sphere *tmp = sp;

	printf("\nSpheres:\n");
	if (!sp)
		printf("  No spheres in the scene.\n");
	while (tmp)
	{
		printf("  Centre: ");
		print_coord(tmp->centre);
		printf("  Diameter: %.2f\n", tmp->diameter);
		printf("  Colour: ");
		print_colour(tmp->colour);
		printf("\n");
		tmp = tmp->next;
	}
}

static void print_planes(t_plane *pl)
{
	t_plane *tmp = pl;

	printf("\nPlanes:\n");
	if (!pl)
		printf("  No planes in the scene.\n");
	while (tmp)
	{
		printf("  Point: ");
		print_coord(tmp->point);
		printf("  Normal Vector: ");
		print_coord(tmp->vector);
		printf("  Colour: ");
		print_colour(tmp->colour);
		printf("\n");
		tmp = tmp->next;
	}
}

static void print_cylinders(t_cylinder *cy)
{
	t_cylinder *tmp = cy;

	printf("\nCylinders:\n");
	if (!cy)
		printf("  No cylinders in the scene.\n");
	while (tmp)
	{
		printf("  Centre: ");
		print_coord(tmp->centre);
		printf("  Normal Vector: ");
		print_coord(tmp->vector);
		printf("  Diameter: %.2f\n", tmp->diameter);
		printf("  Height: %.2f\n", tmp->height);
		printf("  Colour: ");
		print_colour(tmp->colour);
		printf("\n\n");
		tmp = tmp->next;
	}
}

void print_camera(t_camera *c)
{
	printf("Camera:\n");
	printf("  Viewpoint: ");
	print_coord(c->point);
	printf("  Vector: ");
	print_coord(c->vector);
	printf("  View Degree: %d\n", c->view_degree);
}

void print_light(t_light *l)
{
	printf("Light:\n");
	printf("  Position: ");
	print_coord(l->lightpoint);
	printf("  Brightness: %.2f\n", l->brightness);
	printf("  Colour: ");
	print_colour(l->colour);
	printf("\n");
}

void print_ambient(t_ambient *a)
{
	printf("Ambient Light:\n");
	printf("  Ratio: %.2f\n", a->ratio);
	printf("  Colour: ");
	print_colour(a->colour);
	printf("\n");
}

void print_scene(t_scene *scene)
{
	printf("\n--- Scene Parameters ---\n");
	// Ambient Light
	print_ambient(&scene->a);
	// Camera
	print_camera(&scene->c);
	// Light Source
	print_light(&scene->l);
	// Object Counts
	printf("\n--- Object Counts ---\n");
	printf("Spheres: %d\n", scene->sp_count);
	printf("Planes: %d\n", scene->pl_count);
	printf("Cylinders: %d\n", scene->cy_count);
	// Print Objects
	print_spheres(scene->sp);
	print_planes(scene->pl);
	print_cylinders(scene->cy);
	printf("\n");
}

void print_light_math_inputs(t_light_math *inputs)
{
	printf("Normal Vector: (%f, %f, %f)\n", inputs->normal.x, inputs->normal.y, inputs->normal.z);
	printf("Incident Light Vector: (%f, %f, %f)\n", inputs->incident_l.x, inputs->incident_l.y, inputs->incident_l.z);
	printf("Scalar NL: %f\n", inputs->scalar_nl);
	printf("Incident View Vector: (%f, %f, %f)\n", inputs->incident_v.x, inputs->incident_v.y, inputs->incident_v.z);
	printf("Reflected Vector: (%f, %f, %f)\n", inputs->reflected_vector.x, inputs->reflected_vector.y, inputs->reflected_vector.z);
	printf("Scalar VR: %f\n", inputs->scalar_vr);
	printf("Reflectivity: %f\n", inputs->reflectivity);
}

void print_list(t_inter *head, int x, int y)
{
	t_sphere *sp;

	if (!head)
	{
		printf("nothing here\n");
		return;
	}
	int i = 0;
	while (head)
	{
		sp = (t_sphere *)head->obj;
		printf("x: %d y: %d  IN%d: t: %f, [%f, %f, %f], sp[%f, %f, %f]\n", x, y, i, head->distance, head->point.x, head->point.y, head->point.z, sp->centre.x, sp->centre.y, sp->centre.z);
		i++;
		head = head->next;
	}
}

void print_distance(t_inter *head)
{
	t_inter *tmp = head;

	if (!head)
	{
		printf("nothing here\n");
		return;
	}
	while (tmp)
	{
		printf("distance to light %f\n", tmp->dist_to_light);
		tmp = tmp->next;
	}
}

void print_intersections(t_inter ***head, int w, int h)
{
	int y = -1;
	int x = -1;

	if (!head)
	{
		printf("nothing here\n");
		return;
	}
	while (++y < h)
	{
		while (++x < w)
		{
			print_distance(head[y][x]);
		}
	}
}
