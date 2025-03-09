#include "../includes/minirt.h"

int is_numerical(volatile char *str)
{
    int i;
    int has_dot;
    int comma = 0;

    i = 0;
    has_dot = 0;
    comma = 0;
    if (!str || !str[i])
        return (1);
    if (str[i] == '-')
        i++;
    while (str[i] && str[i] != '\n')
    {
        if (str[i] == '.')
        {
            if (has_dot)
                return (0);
            has_dot = 1;
        }
        else if (str[i] == ',')
        {
            if (comma == 2)
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
    int j;

    if (!ft_isalpha(values[0][0]))
    {
        printf("Error: Invalid identifier: %s\n", values[0]);
        return (1);
    }
    j = 1;
    while (values[j])
    {
        if (is_numerical(values[j]))
        {
            printf("Error: Invalid number format: %s\n", values[j]);
            return (1);
        }
        j++;
    }
    return (0);
}
