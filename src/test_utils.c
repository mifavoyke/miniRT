#include "../includes/minirt.h"

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
	printf("\nSpheres:\n");
	if (!sp)
		printf("  No spheres in the scene.\n");
	while (sp)
	{
		printf("  Centre: ");
		print_coord(sp->centre);
		printf("\n  Diameter: %.2f\n", sp->diameter);
		printf("  Colour: ");
		print_colour(sp->colour);
		printf("\n");
		sp = sp->next;
	}
}

static void print_planes(t_plane *pl)
{
	printf("\nPlanes:\n");
	if (!pl)
		printf("  No planes in the scene.\n");
	while (pl)
	{
		printf("  Point: ");
		print_coord(pl->point);
		printf("\n  Normal Vector: ");
		print_coord(pl->vector);
		printf("\n  Colour: ");
		print_colour(pl->colour);
		printf("\n");
		pl = pl->next;
	}
}

static void print_cylinders(t_cylinder *cy)
{
	printf("\nCylinders:\n");
	if (!cy)
		printf("  No cylinders in the scene.\n");
	while (cy)
	{
		printf("  Centre: ");
		print_coord(cy->centre);
		printf("\n  Normal Vector: ");
		print_coord(cy->vector);
		printf("\n  Diameter: %.2f\n", cy->diameter);
		printf("  Height: %.2f\n", cy->height);
		printf("  Colour: ");
		print_colour(cy->colour);
		printf("\n");
		cy = cy->next;
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
