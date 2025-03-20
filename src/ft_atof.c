/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpiarova <zpiarova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 14:13:03 by zpiarova          #+#    #+#             */
/*   Updated: 2025/03/20 14:13:04 by zpiarova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

double ft_atof(char *str)
{
    double result;
    double fraction;
    int sign;
    int i;

    result = 0.0;
    fraction = 0.1;
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
    if (str[i] == '.')
    {
        i++;
        while (ft_isdigit(str[i]))
        {
            result += (str[i] - '0') * fraction;
            fraction *= 0.1;
            i++;
        }
    }
    result *= sign;
    if (result > INT_MAX || result < INT_MIN)
        return (INT_ERROR);
    return (result);
}
