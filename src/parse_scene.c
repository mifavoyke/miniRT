#include "../includes/minirt.h"

void create_test_sphere(t_sphere *sp)
{
	if (!sp)
		return;
	sp->centre = set_default_coord(0.0, 0.0, 20.6);
	sp->diameter = 12.6;
	sp->colour = set_default_colour(10, 0, 255);
	sp->next = NULL;
}

int default_scene(t_scene *scene)
{
	scene->a.ratio = 0.2;								// idk what default values will we choose?
	scene->a.colour = set_default_colour(255, 51, 255); // pink

	scene->c.viewpoint = set_default_coord(-50.0, 0, 20);
	scene->c.vector = set_default_coord(0.0, 0.0, 1.0);
	scene->c.view_degree = 70;

	scene->l.lightpoint = set_default_coord(-40.0, 50.0, 0.0);
	scene->l.brightness = 0.6;
	scene->l.colour = set_default_colour(255, 255, 255);

	// scene->sp = NULL;
	scene->sp = malloc(sizeof(t_sphere));
	if (!scene->sp)
	{
		return (1);
	}
	create_test_sphere(scene->sp);
	scene->pl = NULL;
	scene->cy = NULL;

	scene->sp_count = 1;
	scene->pl_count = 0;
	scene->cy_count = 0;
	return (0);
}

void print_array(char **arr, int size)
{
	printf("\n");
	for (int i = 0; i < size; i++)
		printf("%s", arr[i]);
}

void print_colour(t_colour colour)
{
	printf("(%d, %d, %d)", colour.r, colour.g, colour.b);
}

void print_coord(t_coord coord)
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

// void identify_objects(char **parsed_file, int size)
// {

// }

t_scene *fill_scene(char **rows, int size)
{
	t_scene *scene;
	char **values;
	int i;

	scene = malloc(sizeof(t_scene));
	if (!scene)
		return (NULL);
	default_scene(scene);
	i = 0;
	while (i < size)
	{
		values = ft_split(rows[i], ' ');
		if (!values)
		{
			printf("Error. ft_split failed.\n");
			return (NULL);
		}
		// process the row into the scene
		i++;
	}
	ft_free(values, size);
	return (scene);
}

int parse_scene(t_minirt *minirt, char *rt_file)
{
	char **parsed_file;
	int size;
	(void)minirt;

	size = count_rows(rt_file);
	parsed_file = get_lines(rt_file, size);
	if (!parsed_file)
		return (1);

	print_array(parsed_file, size);

	minirt->scene = fill_scene(parsed_file, size);
	if (!minirt->scene)
		return (1);

	printf("\n");
	print_scene(minirt->scene);
	
	free(minirt->scene->sp);
	free(minirt->scene);
	ft_free(parsed_file, size);
	return (0);
}
