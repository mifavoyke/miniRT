/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zuzanapiarova <zuzanapiarova@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 14:13:03 by zpiarova          #+#    #+#             */
/*   Updated: 2025/04/26 19:28:45 by zuzanapiaro      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

double	get_fractional_part(char *str, int *i)
{
	double	fraction;
	double	fractional_part;

	fraction = 0.1;
	fractional_part = 0.0;
	if (str[*i] == '.')
	{
		(*i)++;
		while (ft_isdigit(str[*i]))
		{
			fractional_part += (str[*i] - '0') * fraction;
			fraction *= 0.1;
			(*i)++;
		}
	}
	return (fractional_part);
}

// converts string to float 
double	ft_atof(char *str)
{
	double	result;
	int		sign;
	int		i;

	result = 0.0;
	sign = 1;
	i = 0;
	if (!str || !str[i])
		return (0);
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	result = (result + get_fractional_part(str, &i)) * sign;
	if (result > INT_MAX || result < INT_MIN)
		return (INT_ERROR);
	return (result);
}
