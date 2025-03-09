#include "../includes/minirt.h"

static void print_colour(t_colour colour)
{
	printf("(%d, %d, %d)", colour.r, colour.g, colour.b);
}

static void print_coord(t_coord coord)
{
	printf("(%.2f, %.2f, %.2f)", coord.x, coord.y, coord.z);
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
	print_coord(scene->c.viewpoint);
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

	printf("\n--- Object Counts ---\n");
	printf("Spheres: %d\n", scene->sp_count);
	printf("Planes: %d\n", scene->pl_count);
	printf("Cylinders: %d\n", scene->cy_count);
}

void create_test_sphere(t_sphere *sp)
{
	if (!sp)
		return;
	sp->centre = set_coord(0.0, 0.0, 20.6);
	sp->diameter = 12.6;
	sp->colour = set_colour(10, 0, 255);
	sp->next = NULL;
}
