/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zuzanapiarova <zuzanapiarova@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 18:29:37 by zuzanapiaro       #+#    #+#             */
/*   Updated: 2025/04/27 10:45:23 by zuzanapiaro      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

// counts all rows of the file
int	count_rows(int fd)
{
	int		i;
	char	*one_line;

	i = 0;
	one_line = get_next_line(fd);
	if (!one_line)
		return (0);
	while (one_line)
	{
		i++;
		free(one_line);
		one_line = NULL;
		one_line = get_next_line(fd);
	}
	free(one_line);
	return (i);
}

// stores lines from the .rt file in an array
// @returns array of lines from the file
char	**get_file_data(int fd, int size)
{
	int		i;
	char	*one_line;
	char	**file_data;

	i = 0;
	one_line = get_next_line(fd);
	if (!one_line)
		return (NULL);
	file_data = (char **)malloc(sizeof(char *) * (size + 1));
	if (!file_data)
	{
		free(one_line);
		return (NULL);
	}
	while (one_line)
	{
		file_data[i] = one_line;
		one_line = get_next_line(fd);
		i++;
	}
	file_data[i] = NULL;
	return (file_data);
}

// creates an allocated array of rows from the .rt file 
char	**store_file_contents(char *filename)
{
	int		size;
	char	**file_data;
	int		fd;

	if (check_file_format(filename))
	{
		ft_error("Wrong scene format. Expected .rt file.");
		return (NULL);
	}
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		ft_error("File not found or has wrong permissions.");
		return (NULL);
	}
	size = count_rows(fd);
	close(fd);
	if (size == 0)
		return (NULL);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (NULL);
	file_data = get_file_data(fd, size);
	close(fd);
	return (file_data);
}
