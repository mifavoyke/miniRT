/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhusieva <yhusieva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 14:13:22 by zpiarova          #+#    #+#             */
/*   Updated: 2025/04/23 18:57:19 by yhusieva         ###   ########.fr       */
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
	printf("  View Degree: %f\n", c->view_degree);
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

// Euclidean space vs Cartesian

void draw_shadow_rays(t_minirt *minirt)
{
	int x, y;
	t_coord intersection_point;
	t_coord light_point = minirt->scene->l.lightpoint;
	t_colour white = set_colour(255, 255, 255, 255);

	for (y = 0; y < minirt->img_height; y++)
	{
		for (x = 0; x < minirt->img_width; x++)
		{
			if (minirt->intersection[y][x])
			{
				intersection_point = minirt->intersection[y][x]->point;
				if (x % 10 == 0 && y % 10 == 0)
					draw_line(minirt, intersection_point, light_point, white);
			}
		}
	}
}

void draw_line(t_minirt *minirt, t_coord start, t_coord end, t_colour color)
{
	float dx = end.x - start.x;
	float dy = end.y - start.y;
	float dz = end.z - start.z;
	float steps = fmax(fmax(fabs(dx), fabs(dy)), fabs(dz));
	float x_inc = dx / steps;
	float y_inc = dy / steps;
	// float z_inc = dz / steps;

	float x = start.x;
	float y = start.y;
	// float z = start.z;
	int i = 0;
	while (i++ < steps)
	{
		int px = (int)x;
		int py = (int)y;
		if (px >= 0 && px < minirt->img_width && py >= 0 && py < minirt->img_height)
			minirt->pixels[py][px] = color;
		x += x_inc;
		y += y_inc;
		// z += z_inc;
	}
}
