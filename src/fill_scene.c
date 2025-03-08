#include "../includes/minirt.h"

int fill_ambient(t_scene *scene, char **values)
{
    if (!values[1] || !values[2])
    {
        printf("Error: Ambient Light missing parameters.\n");
        return (1);
    }
    scene->a.ratio = ft_atof(values[1]);
    if (scene->a.ratio < 0.0 || scene->a.ratio > 1.0)
    {
        printf("Error: Ambient ratio out of range. Using default 0.2.\n");
        scene->a.ratio = 0.2;
    }
    scene->a.colour = parse_colour(values[2]);
    return (0);
}

int fill_camera(t_scene *scene, char **values)
{
    if (!values[1] || !values[2] || !values[3])
    {
        printf("Error: Camera missing parameters.\n");
        return (1);
    }
    scene->c.viewpoint = parse_coord(values[1]);
    scene->c.vector = parse_coord(values[2]);
    if (scene->c.vector.x < -1 || scene->c.vector.x > 1 ||
        scene->c.vector.y < -1 || scene->c.vector.y > 1 ||
        scene->c.vector.z < -1 || scene->c.vector.z > 1)
    {
        printf("Error: Camera orientation vector out of range. Using default (0,0,1).\n");
        scene->c.vector = set_coord(0.0, 0.0, 1.0);
    }
    scene->c.view_degree = ft_atoi(values[3]);
    if (scene->c.view_degree < 0 || scene->c.view_degree > 180)
    {
        printf("Error: Camera field of view out of range. Using default 70.\n");
        scene->c.view_degree = 70;
    }
    return (0);
}

int fill_light(t_scene *scene, char **values)
{
    if (!values[1] || !values[2] || !values[3])
    {
        printf("Error: Light missing parameters.\n");
        return (1);
    }
    scene->l.lightpoint = parse_coord(values[1]);
    scene->l.brightness = ft_atof(values[2]);
    if (scene->l.brightness < 0.0 || scene->l.brightness > 1.0)
    {
        printf("Error: Light brightness out of range. Using default 0.6.\n");
        scene->l.brightness = 0.6;
    }
    scene->l.colour = parse_colour(values[3]);
    return (0);
}

int identify_objects(t_scene *scene, char *first_letter, char **values)
{
    if (!ft_strncmp(first_letter, "A", 1))
        return (fill_ambient(scene, values));
    else if (!ft_strncmp(first_letter, "C", 1))
        return (fill_camera(scene, values));
    else if (!ft_strncmp(first_letter, "L", 1))
        return (fill_light(scene, values));
    printf("No A, C or L has been indentified.\n");
    return (0);
}

// int is_numerical(const char *str)
// {
//     int i;
//     int has_dot;
//     int comma;

//     i = 0;
//     if (!str || !str[i])
//         return (0);
//     if (str[i] == '-')
//         i++;
//     has_dot = 0;
//     comma = 0;
//     while (str[i] || str[i] != '\n')
//     {
//         if (str[i] == '.')
//         {
//             if (has_dot)
//             {
//                 printf("dots\n");
//                 return (0);
//             }
//             has_dot = 1;
//         }
//         else if (str[i] == ',')
//         {
//             if (comma == 2)
//             {
//                 printf("commas\n");
//                 return (0);
//             }
//             comma++;
//         }
//         else if (!ft_isdigit(str[i]))
//         {
//             printf("is digit\n");
//             return (0);
//         }
//         i++;
//     }
//     return (1);
// }

// int valid_input(char **values)
// {
//     int j;

//     if (!ft_isalpha(values[0][0]))
//     {
//         printf("Error: Invalid identifier: %s\n", values[0]);
//         return (0);
//     }
//     j = 1;
//     while (values[j])
//     {
//         if (!is_numerical(values[j]))
//         {
//             printf("Error: Invalid number format: %s\n", values[j]);
//             return (0);
//         }
//         j++;
//     }
//     return (1);
// }

t_scene *fill_scene(char **rows, int size)
{
    t_scene *scene;
    char **values;
    int i;

    scene = malloc(sizeof(t_scene));
    if (!scene)
        return (NULL);
    default_scene(scene);
    i = 0;
    while (i < size)
    {
        values = ft_split(rows[i], ' ');
        if (!values)
        {
            printf("Error: ft_split failed.\n");
            return (NULL);
        }
        // if (!valid_input(values))
        // {
        //     // free something?
        //     return (NULL);
        // }
        if (identify_objects(scene, values[0], values))
        {
            printf("Error: Invalid object definition at line %d.\n", i + 1);
            // ft_free(values, );
            return (NULL);
        }
        // ft_free(values, ); // make a ft to count the num of words
        i++;
    }
    return (scene);
}
