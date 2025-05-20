/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhusieva <yhusieva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 10:09:26 by zuzanapiaro       #+#    #+#             */
/*   Updated: 2025/05/20 15:59:20 by yhusieva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

// returns true(1) if character is space, tab, newline or other whitespace
int	ft_is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n'
		|| c == '\f' || c == '\r' || c == '\v');
}

// eliminates empty lines
// empty lines are result of line with only whitespaces or only comments 
// called after all whitespace is turned to spaces
// returns 1 if is epmty, 0 if there is other value than space 
int	is_empty_line(char *line)
{
	while (*line)
	{
		if (*line != ' ')
			return (0);
		line++;
	}
	return (1);
}

// checks if the value already contains 1 dot or 3 commas
// if it contains more, it it over the limit
// returns 1 if string contains dot/3 commas, 0 if not
int	dot_comma_limit(char *str, int *i, int *comma, int *has_dot)
{
	if (str[*i] == '.')
	{
		if ((*has_dot && !ft_strchr(str, ',')) || *has_dot > 3)
			return (1);
		(*has_dot)++;
	}
	if (str[*i] == ',')
	{
		if (str[(*i) + 1] == '-')
			(*i)++;
		if (*comma >= 2)
			return (1);
		(*comma)++;
	}
	return (0);
}

// checks if the string is either a coordinate or integer or float
// returns 1 if numerical(coordinate/float/int), 0 if not numerical
int	is_numerical(char *str)
{
	int	i;
	int	has_dot;
	int	comma;

	i = 0;
	has_dot = 0;
	comma = 0;
	if (!str || !str[i])
		return (1);
	if (str[i] == '-')
		i++;
	while (str[i] && str[i] != '\n')
	{
		if (dot_comma_limit(str, &i, &comma, &has_dot))
			return (0);
		else if (!ft_isdigit(str[i])
			&& str[i] != ',' && str[i] != '.' && str[i] != '-')
			return (0);
		i++;
	}
	return (1);
}

// frees the array
void	free_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	arr = NULL;
}
