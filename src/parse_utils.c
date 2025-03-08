#include "../includes/minirt.h"

t_coord set_coord(float x, float y, float z) // add some range checks?
{
	t_coord coord;

	coord.x = x;
	coord.y = y;
	coord.z = z;
	return (coord);
}

t_colour set_colour(int r, int b, int g)
{
	t_colour clr;

	clr.r = r;
	clr.b = b;
	clr.g = g;
	return (clr);
}

t_coord parse_coord(char *coord)
{
	t_coord parsed;
	char **values;

	values = ft_split(coord, ',');
	if (!values || !values[0] || !values[1] || !values[2])
	{
		printf("Error: Invalid coordinate format. Using default (0,0,0).\n");
		return (set_coord(0.0, 0.0, 0.0));
	}
	parsed.x = ft_atof(values[0]);
	parsed.y = ft_atof(values[1]);
	parsed.z = ft_atof(values[2]);
	ft_free(values, 3);
	return (parsed);
}

t_colour parse_colour(char *clr)
{
	t_colour colour;
	char **values;

	values = ft_split(clr, ',');
	if (!values || !values[0] || !values[1] || !values[2])
	{
		printf("Error: Invalid colour format.\n");
		return (set_colour(255, 255, 255));
	}
	colour.r = ft_atoi(values[0]);
	colour.g = ft_atoi(values[1]);
	colour.b = ft_atoi(values[2]);
	ft_free(values, 3);
	if (colour.r < 0 || colour.r > 255 || colour.g < 0 || colour.g > 255 || colour.b < 0 || colour.b > 255)
	{
		printf("Error: Colour values out of range. Using default.\n");
		return (set_colour(255, 255, 255));
	}
	return (colour);
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
