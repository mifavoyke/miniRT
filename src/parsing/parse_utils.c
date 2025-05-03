/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhusieva <yhusieva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 10:06:08 by zuzanapiaro       #+#    #+#             */
/*   Updated: 2025/05/03 11:09:10 by yhusieva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

// checks if the last 3 characters of the file name are .rt
int	check_file_format(char *filename)
{
	int	i;

	i = 0;
	while (filename[i])
	{
		if (filename[i] == '.'
			&& filename[i + 1] == 'r'
			&& filename[i + 2] == 't'
			&& filename[i + 3] == '\0')
			return (0);
		i++;
	}
	return (ERROR);
}

// normalizes whitespace for one row
char	*normalise_whitespace(char *str)
{
	int		i;
	int		j;
	char	*new_str;

	i = 0;
	j = 0;
	new_str = (char *)malloc(ft_strlen(str) + 1);
	if (!new_str)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '#')
		{
			while (str[i] && str[i] != '\n')
				i++;
			break ;
		}
		else if (ft_is_space(str[i]))
			new_str[j++] = ' ';
		else
			new_str[j++] = str[i];
		i++;
	}
	new_str[j] = '\0';
	return (new_str);
}

// checks if input has correct values
// @returns 1 if valid, 0 if not valid
int	is_valid_input(char **values)
{
	int	i;

	if (!values || !values[0])
		return (1);
	if (!ft_isalpha(values[0][0]))
		return (0);
	i = 1;
	while (values[i])
	{
		if (!is_numerical(values[i]))
			return (0);
		i++;
	}
	return (1);
}
