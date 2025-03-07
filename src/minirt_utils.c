#include "../includes/minirt.h"

void ft_error(void)
{
	fprintf(stderr, "%s", mlx_strerror(mlx_errno)); // replace the function for the norm
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

