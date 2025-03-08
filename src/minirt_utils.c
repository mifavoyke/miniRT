#include "../includes/minirt.h"

void ft_error(void)
{
	fprintf(stderr, "Error\n%s", mlx_strerror(mlx_errno)); // replace the function for the norm
    // exit (1);
}

void ft_free(char **arr, int size)
{
    int i;

    i = 0;
    while (i < size)
    {
        free(arr[i]);
        i++;
    }
    free(arr);
}

int check_file_format(char *filename)
{
	int i;

	i = 0;
	while (filename[i])
	{
		if (filename[i] == '.' && filename[i + 1] == 'r' && filename[i + 2] == 't' && filename[i + 3] == '\0')
			return (0);
		i++;
	}
	return (1);
}
