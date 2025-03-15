#include "../../includes/minirt.h"

int store_pixel(t_pixel *p, t_colour cl, void *obj, int obj_t)
{
    p->cl = cl;
    p->obj = obj;
    p->obj_type = obj_t;
    // p->distance = ???;
    return (0);
}

t_pixel **allocate_pixels(int width, int height)
{
	t_pixel **pixels;
	int y;

	pixels = (t_pixel **)malloc(height * sizeof(t_pixel *));
	if (!pixels)
		return (NULL);
	y = -1;
	while (++y < height)
	{
		pixels[y] = (t_pixel *)malloc(width * sizeof(t_pixel));
		if (!pixels[y])
			return (NULL);
	}
	return (pixels);
}

void init_pixels(t_minirt *minirt)
{
	int x;
	int y;

	y = -1;
	while (++y < minirt->img_height)
	{
		x = -1;
		while (++x < minirt->img_width)
		{
			minirt->pixels[y][x].cl = apply_ambience(&minirt->scene->background, &minirt->scene->a.colour, minirt->scene->a.ratio);
			// minirt->pixels[y][x].obj = ;
			minirt->pixels[y][x].obj_type = NO_OBJ;
			// minirt->pixels[y][x].distance = ???;
		}
	}
}
