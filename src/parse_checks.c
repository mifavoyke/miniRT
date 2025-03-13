#include "../includes/minirt.h"

// static int is_numerical(volatile char *str)
// {
//     int i;
//     int has_dot;
//     int comma = 0;

//     i = 0;
//     has_dot = 0;
//     comma = 0;
//     if (!str || !str[i])
//         return (1);
//     if (str[i] == '-')
//         i++;
//     while (str[i] && str[i] != '\n')
//     {
//         if (str[i] == '.')
//         {
//             if (has_dot)
//                 return (1);
//             has_dot = 1;
//         }
//         else if (str[i] == ',')
//         {
//             if (str[i + 1] == '-')
//                 i++;
//             if (comma == 2)
//                 return (1);
//             comma++;
//         }
//         else if (!ft_isdigit(str[i]))
//             return (1);
//         i++;
//     }
//     return (0);
// }

int valid_input(char **values)
{
    int i;

    if (!ft_isalpha(values[0][0]))
        return (ft_error(values[0]));
    i = 1;
    // while (values[i])
    // {
    //     if (is_numerical(values[i]))
    //         return (ft_error(values[i]));
    //     i++;
    // }
    return (0);
}
