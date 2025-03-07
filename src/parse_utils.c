#include "../includes/minirt.h"

t_colour set_default_colour(int r, int b, int g)
{
	t_colour clr;
	int bottom;
	int top;

	bottom = 0;
	top = 255;
	if (r < bottom || r > top || b < bottom || b > top || g < bottom || g > top)
	{
		printf("Wrong colour range. RGB values must be within [0, 255]\nSetting the default white colour...\n");
		clr.r = clr.b = clr.g = 255;
		return (clr);
	}
	clr.r = r;
	clr.b = b;
	clr.g = g;
	return (clr);
}

t_coord set_default_coord(float x, float y, float z) // add some range checks?
{
	t_coord coord;

	coord.x = x;
	coord.y = y;
	coord.z = z;
	return (coord);
}

int	count_rows(char *arg)
{
	char	*one_line;
	int		fd;
	int	i;

	i = 0;
	fd = open(arg, O_RDONLY);
	if (fd == -1)
		return (0);
	one_line = get_next_line(fd);
	if (!one_line)
		return (0);
	while (one_line != NULL)
	{
		i++;
		free(one_line);
		one_line = get_next_line(fd);
	}
	close(fd);
	return (i);
}

char	**get_lines(char *arg, int size)
{
	char	**read_lines;
	char	*one_line;
	int		i;
	int		fd;

	i = 0;
	read_lines = NULL;
	fd = open(arg, O_RDONLY);
	if (fd == -1)
		return (NULL);
	one_line = get_next_line(fd);
	if (!one_line)
		return (NULL);
	read_lines = (char **)malloc(size * sizeof(char *));
	if (read_lines == NULL)
		return (NULL);
	while (one_line != NULL)
	{
		read_lines[i] = one_line;
		one_line = get_next_line(fd);
		i++;
	}
	free(one_line);
	close(fd);
	return (read_lines);
}
