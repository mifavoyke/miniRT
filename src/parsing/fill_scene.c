/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhusieva <yhusieva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 14:11:24 by zpiarova          #+#    #+#             */
/*   Updated: 2025/04/10 14:25:41 by yhusieva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

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
    scene->c.point = parse_coord(values[1]);
    if (valid_coord(&scene->c.point))
        return (1);
    scene->c.vector = parse_coord(values[2]);
    if (!is_vector_normalized(scene->c.vector))
    {
        if (!scene->c.vector.x && !scene->c.vector.y && !scene->c.vector.z)
            return (ft_error("Camera orientation vector cannot be (0,0,0)."));
        normalize(&scene->c.vector);
        // return (ft_error("Camera orientation vector is not normalised."));
    }
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
    // if (fill_sphere(scene, values))
    //     return (1);
    return (0);
}

int fill_sphere(t_scene *scene, char **values)
{
    t_sphere *new_sphere;
    t_sphere *tmp;

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
    new_sphere->next = NULL;
    if (!scene->sp)
        scene->sp = new_sphere;
    else
    {
        tmp = scene->sp;
        while (tmp->next)
            tmp = tmp->next;
        tmp->next = new_sphere;
    }
    scene->sp_count++;
    return (0);
}

int fill_plane(t_scene *scene, char **values)
{
    t_plane *new_plane;
    t_plane *tmp;

    if (!values[1] || !values[2] || !values[3])
        return (ft_error("Plane missing parameters."));
    new_plane = malloc(sizeof(t_plane));
    if (!new_plane)
        return (ft_error("Memory allocation failed for plane."));
    new_plane->point = parse_coord(values[1]);
    if (valid_coord(&new_plane->point))
        return (1);
    new_plane->vector = parse_coord(values[2]);
    if (!is_vector_normalized(new_plane->vector))
    {
        if (!new_plane->vector.x && !new_plane->vector.y && !new_plane->vector.z)
            return (ft_error("Plane normal vector cannot be (0,0,0)."));
        normalize(&new_plane->vector);
        // return (ft_error("Plane normal vector is not normalised."));
    }
    new_plane->colour = parse_colour(values[3]);
    if (valid_colour(&new_plane->colour))
        return (1);

    new_plane->next = NULL;
    if (!scene->pl)
        scene->pl = new_plane;
    else
    {
        tmp = scene->pl;
        while (tmp->next)
            tmp = tmp->next;
        tmp->next = new_plane;
    }

    // new_plane->next = scene->pl;
    // scene->pl = new_plane;
    scene->pl_count++;
    return (0);
}

int fill_cylinder(t_scene *scene, char **values)
{
    t_cylinder *new_cylinder;
    t_cylinder *tmp;

    if (!values[1] || !values[2] || !values[3] || !values[4] || !values[5])
        return (ft_error("Cylinder missing parameters."));
    new_cylinder = malloc(sizeof(t_cylinder));
    if (!new_cylinder)
        return (ft_error("Memory allocation failed for cylinder."));
    new_cylinder->centre = parse_coord(values[1]);
    if (valid_coord(&new_cylinder->centre))
        return (1);
    new_cylinder->vector = parse_coord(values[2]);
    if (!is_vector_normalized(new_cylinder->vector))
    {
        if (!new_cylinder->vector.x && !new_cylinder->vector.y && !new_cylinder->vector.z)
            return (ft_error("Cylinder orientation vector cannot be (0,0,0)."));
        normalize(&new_cylinder->vector);
        // return (ft_error("Cylinder orientation vector is not normalised."));
    }
    new_cylinder->diameter = ft_atof(values[3]);
    if (new_cylinder->diameter <= 0)
        return (ft_error("Cylinder diameter must be greater than zero."));
    new_cylinder->height = ft_atof(values[4]);
    if (new_cylinder->height <= 0)
        return (ft_error("Cylinder height must be greater than zero."));
    new_cylinder->colour = parse_colour(values[5]);
    if (valid_colour(&new_cylinder->colour))
        return (1);

    new_cylinder->next = NULL;
    if (!scene->cy)
        scene->cy = new_cylinder;
    else
    {
        tmp = scene->cy;
        while (tmp->next)
            tmp = tmp->next;
        tmp->next = new_cylinder;
    }

    // new_cylinder->next = scene->cy;
    // scene->cy = new_cylinder;
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
