/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhusieva <yhusieva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 14:13:22 by zpiarova          #+#    #+#             */
/*   Updated: 2025/03/22 14:32:47 by yhusieva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static void print_colour(t_colour colour)
{
	printf("(%d, %d, %d)", colour.r, colour.g, colour.b);
}

static void print_coord(t_coord coord)
{
	printf("(%.2f, %.2f, %.2f)", coord.x, coord.y, coord.z);
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
		printf("\n  Diameter: %.2f\n", tmp->diameter);
		printf("  Colour: ");
		print_colour(tmp->colour);
		printf("\n\n");
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
		printf("\n  Normal Vector: ");
		print_coord(tmp->vector);
		printf("\n  Colour: ");
		print_colour(tmp->colour);
		printf("\n\n");
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
		printf("\n  Normal Vector: ");
		print_coord(tmp->vector);
		printf("\n  Diameter: %.2f\n", tmp->diameter);
		printf("  Height: %.2f\n", tmp->height);
		printf("  Colour: ");
		print_colour(tmp->colour);
		printf("\n\n");
		tmp = tmp->next;
	}
}

void print_scene(t_scene *scene)
{
	printf("\n--- Scene Parameters ---\n");

	// Ambient Light
	printf("Ambient Light:\n");
	printf("  Ratio: %.2f\n", scene->a.ratio);
	printf("  Colour: ");
	print_colour(scene->a.colour);
	printf("\n");

	// Camera
	printf("\nCamera:\n");
	printf("  Viewpoint: ");
	print_coord(scene->c.point);
	printf("\n  Vector: ");
	print_coord(scene->c.vector);
	printf("\n  View Degree: %d\n", scene->c.view_degree);

	// Light Source
	printf("\nLight:\n");
	printf("  Position: ");
	print_coord(scene->l.lightpoint);
	printf("\n  Brightness: %.2f\n", scene->l.brightness);
	printf("  Colour: ");
	print_colour(scene->l.colour);
	printf("\n");

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
