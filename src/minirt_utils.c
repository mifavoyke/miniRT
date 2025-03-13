/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpiarova <zpiarova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 17:06:31 by zpiarova          #+#    #+#             */
/*   Updated: 2025/03/13 17:06:33 by zpiarova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void ft_error_mlx(void)
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
