/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zuzanapiarova <zuzanapiarova@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 17:06:31 by zpiarova          #+#    #+#             */
/*   Updated: 2025/04/17 21:22:29 by zuzanapiaro      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

int ft_error(const char *msg)
{
	printf("Error: %s\n", msg);
	return (ERROR);
}

int valid_coord(t_coord *coord)
{
	return (coord->x == INT_ERROR && coord->y == INT_ERROR && coord->z == INT_ERROR);
}

int valid_colour(t_colour *clr)
{
	return (clr->r == -1 && clr->r == -1 && clr->r == -1);
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
	return (ERROR);
}
