#include "../includes/minirt.h"

int ft_error(const char *msg)
{
    printf("Error: %s\n", msg);
    return (1);
}

int valid_coord(t_coord *coord)
{
    return (coord->x == INT_ERROR && coord->y == INT_ERROR && coord->z == INT_ERROR);
}

int valid_vector(t_coord *coord)
{
    return (coord->x < -1 || coord->x > 1 || coord->y < -1 || coord->y > 1 || coord->z < -1 || coord->z > 1);
}

int valid_colour(t_colour *clr)
{
    return (clr->r == -1 && clr->r == -1 && clr->r == -1);
}

int fill_ambient(t_scene *scene, char **values)
{
    scene->a_count++;
    if (scene->a_count > 1)
        return (ft_error("Dublicate Ambient Light has been detected."));
    if (!values[1] || !values[2])
        return (ft_error("Ambient Light missing parameters."));
    scene->a.ratio = ft_atof(values[1]);
    if (scene->a.ratio < 0.0 || scene->a.ratio > 1.0)
        return (ft_error("Ambient ratio out of range."));
    scene->a.colour = parse_colour(values[2]);
    if (valid_colour(&scene->a.colour))
        return (1);
    return (0);
}

int fill_camera(t_scene *scene, char **values)
{
    scene->c_count++;
    if (scene->c_count > 1)
        return (ft_error("Dublicate Camera has been detected."));
    if (!values[1] || !values[2] || !values[3])
        return (ft_error("Camera missing parameters."));
    scene->c.viewpoint = parse_coord(values[1]);
    if (valid_coord(&scene->c.viewpoint))
        return (1);
    scene->c.vector = parse_coord(values[2]);
    if (valid_vector(&scene->c.vector))
        return (ft_error("Camera orientation vector out of range."));
    scene->c.view_degree = ft_atoi(values[3]);
    if (scene->c.view_degree < 0 || scene->c.view_degree > 180)
        return (ft_error("Camera field of view out of range."));
    return (0);
}

int fill_light(t_scene *scene, char **values)
{
    scene->l_count++;
    if (scene->l_count > 1)
        return (ft_error("Dublicate Light has been detected."));
    if (!values[1] || !values[2] || !values[3])
        return (ft_error("Light missing parameters."));
    scene->l.lightpoint = parse_coord(values[1]);
    if (valid_coord(&scene->l.lightpoint))
        return (1);
    scene->l.brightness = ft_atof(values[2]);
    if (scene->l.brightness < 0.0 || scene->l.brightness > 1.0)
        return (ft_error("Light brightness out of range."));
    scene->l.colour = parse_colour(values[3]);
    if (valid_colour(&scene->l.colour))
        return (1);
    return (0);
}

int identify_objects(t_scene *scene, char *first_letter, char **values)
{
    scene->a_count = 0;
    scene->c_count = 0;
    scene->l_count = 0;
    scene->sp_count = 0;
    scene->pl_count = 0;
    scene->cy_count = 0;

    if (!ft_strncmp(first_letter, "A", 1))
        return (fill_ambient(scene, values));
    else if (!ft_strncmp(first_letter, "C", 1))
        return (fill_camera(scene, values));
    else if (!ft_strncmp(first_letter, "L", 1))
        return (fill_light(scene, values));
    return (0);
}

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
        if (valid_input(values))
        {
            // free something?
            return (NULL);
        }
        if (identify_objects(scene, values[0], values))
        {
            // ft_free(values, );
            return (NULL);
        }
        // ft_free(values, ); // make a ft to count the num of words
        i++;
    }
    return (scene);
}
