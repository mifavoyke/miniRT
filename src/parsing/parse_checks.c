/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_checks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpiarova <zpiarova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 14:11:35 by zpiarova          #+#    #+#             */
/*   Updated: 2025/03/20 14:11:39 by zpiarova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static void negative(char c, int *i)
{
    if (c == '-')
        (*i)++;
}

static int is_numerical(char *str)
{
    int i;
    int has_dot;
    int comma = 0;

    i = 0;
    has_dot = 0;
    comma = 0;
    if (!str || !str[i])
        return (1);
    negative(str[i], &i);
    while (str[i] && str[i] != '\n')
    {
        if (str[i] == '.')
        {
            if ((has_dot && !ft_strchr(str, ',')) || has_dot > 3)
                return (1);
            has_dot++;
        }
        else if (str[i] == ',')
        {
            negative(str[i + 1], &i);
            if (comma >= 2)
                return (1);
            comma++;
        }
        else if (!ft_isdigit(str[i]))
            return (1);
        i++;
    }
    return (0);
}

int valid_input(char **values)
{
    int i;

    if (values[0] == NULL)
        return (0);
    if (!ft_isalpha(values[0][0]))
        return (ft_error(values[0]));
    i = 1;
    while (values[i])
    {
        if (is_numerical(values[i]))
            return (ft_error(values[i]));
        i++;
    }
    return (0);
}
