/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhusieva <yhusieva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 14:13:22 by zpiarova          #+#    #+#             */
/*   Updated: 2025/05/03 11:34:34 by yhusieva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

// prints linked list
void	print_list(t_inter *head, int x, int y)
{
	if (!head)
		return ;
	printf("[%d, %d] -----------------------------------------------\n", x, y);
	while (head)
	{
		printf("Intersection point: (%f, %f, %f) distance: %f, object: %d\n",
			head->point.x, head->point.y, head->point.z,
			head->distance, head->type);
		head = head->next;
	}
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
		print_coord(tmp->vector);
		printf("  Diameter: %.2f\n", tmp->diameter);
		printf("  Height: %.2f\n", tmp->height);
		printf("  Colour: ");
		print_colour(tmp->colour);
		printf("\n\n");
		tmp = tmp->next;
	}
}

void	print_camera(t_camera *c)
{
	printf("Camera:\n");
	printf("  Viewpoint: ");
	print_coord(c->point);
	printf("  Vector: ");
	print_coord(c->vector);
	printf("  View Degree: %.2f\n", c->view_degree);
}

void	print_light(t_light *l)
{
	printf("Light:\n");
	printf("  Position: ");
	print_coord(l->lightpoint);
	printf("  Brightness: %.2f\n", l->brightness);
	printf("  Colour: ");
	print_colour(l->colour);
	printf("\n");
}

void	print_ambient(t_ambient *a)
{
	printf("Ambient Light:\n");
	printf("  Ratio: %.2f\n", a->ratio);
	printf("  Colour: ");
	print_colour(a->colour);
	printf("\n");
}

// prints the scene with all its attributes
void	print_scene(t_scene *scene)
{
	printf("\n=== Scene Parameters ===\n");
	print_ambient(&scene->a);
	print_camera(&scene->c);
	print_light(&scene->l);
	printf("\n--- Object Counts ---\n");
	printf("Spheres: %d\n", scene->sp_count);
	printf("Planes: %d\n", scene->pl_count);
	printf("Cylinders: %d\n", scene->cy_count);
	print_spheres(scene->sp);
	print_planes(scene->pl);
	print_cylinders(scene->cy);
}

// Tm = [ Rx  Fx  Ux  Tx ]   [ P0x ]
//		[ Ry  Fy  Uy  Ty ] * [ P0y ]
//		[ Rz  Fz  Uz  Tz ] * [ P0z ]
//		[  0   0   0   1 ] * [  1  ]
void	print_tm(t_matrix Tm)
{
	printf("\nTM:");
	printf("\t[ %f  %f  %f  %f ]\n", Tm.R.x, Tm.F.x, Tm.U.x, Tm.Tr.x);
	printf("\t[ %f  %f  %f  %f ]\n", Tm.R.y, Tm.F.y, Tm.U.y, Tm.Tr.y);
	printf("\t[ %f  %f  %f  %f ]\n", Tm.R.z, Tm.F.z, Tm.U.z, Tm.Tr.z);
	printf("\t[ %f  %f  %f  %f ]\n", 0.0, 0.0, 0.0, 1.0);
}
