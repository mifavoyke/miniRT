/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zuzanapiarova <zuzanapiarova@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 10:52:46 by zpiarova          #+#    #+#             */
/*   Updated: 2025/05/15 11:37:01 by zuzanapiaro      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

// prints possible key controls 
void	print_controls(void)
{
	printf("=== MINI-RT CONTROLS ===\n");
	printf("Close Program:\n");
	printf("  [ESC]             → Exit the program\n");
	printf("Camera Position:\n");
	printf("  [W] / [S]         → Move camera up/down (Z-axis)\n");
	printf("  [A] / [D]         → Move camera left/right (X-axis)\n");
	printf("  Scroll            → Zoom in/out (Y-axis forward/back)\n");
	printf("Camera Rotation:\n");
	printf("  [UP] / [DOWN]     → Pitch (rotate around X-axis - up/down)\n");
	printf("  [J] / [K]         → Roll (rotate Y-axis - tilt to sides)\n");
	printf("  [LEFT] / [RIGHT]  → Yaw (rotate around Z-axis-left/right)\n");
	printf("Resizing objects:\n");
	printf("  diameter increase → drag object right\n");
	printf("  diameter decrease → drag object left\n");
	printf("  height increase   → drag object up\n");
	printf("  height decrease   → drag object down\n");
	printf("========================\n");
}

static void	print_spheres(t_sphere *sp)
{
	t_sphere	*tmp;

	tmp = sp;
	printf("\nSpheres:\n");
	if (!sp)
		printf("  No spheres in the scene.\n");
	while (tmp)
	{
		printf("  ID: %d\n", tmp->id);
		printf("  Centre: ");
		print_coord(tmp->centre);
		printf("  Diameter: %.2f\n", tmp->diameter);
		printf("  Colour: ");
		print_colour(tmp->colour);
		printf("\n");
		tmp = tmp->next;
	}
}

static void	print_planes(t_plane *pl)
{
	t_plane	*tmp;

	tmp = pl;
	printf("\nPlanes:\n");
	if (!pl)
		printf("  No planes in the scene.\n");
	while (tmp)
	{
		printf("  ID: %d\n", tmp->id);
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

static void	print_cylinders(t_cylinder *cy)
{
	t_cylinder	*tmp;

	tmp = cy;
	printf("\nCylinders:\n");
	if (!cy)
		printf("  No cylinders in the scene.\n");
	while (tmp)
	{
		printf("  ID: %d\n", tmp->id);
		printf("  Centre: ");
		print_coord(tmp->centre);
		printf("  Normal Vector: ");
		print_coord(tmp->axis);
		printf("  Diameter: %.2f\n", tmp->diameter);
		printf("  Height: %.2f\n", tmp->h);
		printf("  Colour: ");
		print_colour(tmp->colour);
		printf("\n\n");
		tmp = tmp->next;
	}
}

// prints the scene with all its attributes
void	print_scene(t_scene *scene)
{
	printf("\n=== Scene Parameters ===\n");
	printf("Ambient Light:\n");
	printf("  Ratio: %.2f\n", scene->a.ratio);
	printf("  Colour: ");
	print_colour(scene->a.colour);
	printf("\n");
	printf("Camera:\n");
	printf("  Viewpoint: ");
	print_coord(scene->c.point);
	printf("  Vector: ");
	print_coord(scene->c.vector);
	printf("  View Degree: %.2f\n", scene->c.view_degree);
	printf("Light:\n");
	printf("  Position: ");
	print_coord(scene->l->lightpoint);
	printf("  Brightness: %.2f\n", scene->l->brightness);
	printf("  Colour: ");
	print_colour(scene->l->colour);
	printf("\n");
	print_spheres(scene->sp);
	print_planes(scene->pl);
	print_cylinders(scene->cy);
}
