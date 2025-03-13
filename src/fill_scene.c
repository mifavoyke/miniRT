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

int fill_sphere(t_scene *scene, char **values)
{
    t_sphere *new_sphere;

    if (!values[1] || !values[2] || !values[3])
        return (ft_error("Sphere missing parameters."));
    new_sphere = malloc(sizeof(t_sphere));
    if (!new_sphere)
        return (ft_error("Memory allocation failed for sphere."));
    new_sphere->centre = parse_coord(values[1]);
    if (valid_coord(&new_sphere->centre))
        return (1);
    new_sphere->diameter = ft_atof(values[2]);
    if (new_sphere->diameter <= 0)
        return (ft_error("Sphere diameter must be greater than zero."));
    new_sphere->colour = parse_colour(values[3]);
    if (valid_colour(&new_sphere->colour))
        return (1);
    new_sphere->next = scene->sp;
    scene->sp = new_sphere;
    scene->sp_count++;
    return (0);
}

int fill_plane(t_scene *scene, char **values)
{
    t_plane *new_plane;

    if (!values[1] || !values[2] || !values[3])
        return (ft_error("Plane missing parameters."));
    new_plane = malloc(sizeof(t_plane));
    if (!new_plane)
        return (ft_error("Memory allocation failed for plane."));
    new_plane->point = parse_coord(values[1]);
    if (valid_coord(&new_plane->point))
        return (1);
    new_plane->vector = parse_coord(values[2]);
    if (valid_vector(&new_plane->vector))
        return (ft_error("Plane normal vector out of range."));
    new_plane->colour = parse_colour(values[3]);
    if (valid_colour(&new_plane->colour))
        return (1);
    new_plane->next = scene->pl;
    scene->pl = new_plane;
    scene->pl_count++;
    return (0);
}

int fill_cylinder(t_scene *scene, char **values)
{
    t_cylinder *new_cylinder;

    if (!values[1] || !values[2] || !values[3] || !values[4] || !values[5])
        return (ft_error("Cylinder missing parameters."));
    new_cylinder = malloc(sizeof(t_cylinder));
    if (!new_cylinder)
        return (ft_error("Memory allocation failed for cylinder."));
    new_cylinder->centre = parse_coord(values[1]);
    if (valid_coord(&new_cylinder->centre))
        return (1);
    new_cylinder->vector = parse_coord(values[2]);
    if (valid_vector(&new_cylinder->vector))
        return (ft_error("Cylinder orientation vector out of range."));
    new_cylinder->diameter = ft_atof(values[3]);
    if (new_cylinder->diameter <= 0)
        return (ft_error("Cylinder diameter must be greater than zero."));
    new_cylinder->height = ft_atof(values[4]);
    if (new_cylinder->height <= 0)
        return (ft_error("Cylinder height must be greater than zero."));
    new_cylinder->colour = parse_colour(values[5]);
    if (valid_colour(&new_cylinder->colour))
        return (1);
    new_cylinder->next = scene->cy;
    scene->cy = new_cylinder;
    scene->cy_count++;
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
    else if (!ft_strncmp(first_letter, "sp", 2))
        return (fill_sphere(scene, values));
    else if (!ft_strncmp(first_letter, "pl", 2))
        return (fill_plane(scene, values));
    else if (!ft_strncmp(first_letter, "cy", 2))
        return (fill_cylinder(scene, values));
    return (ft_error("Unknown object type."));
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
