/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpiarova <zpiarova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 14:11:24 by zpiarova          #+#    #+#             */
/*   Updated: 2025/05/09 10:53:18 by zpiarova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

// creates the ambient object only if it is the first one to exist
// if any exists before, exits
// expects: A  ratio<0,1>  colour(r,g,b)
int	fill_ambient(t_scene *scene, char **values)
{
	scene->a_count++;
	if (scene->a_count > 1)
		return (ft_error("Dublicate Ambient Light has been detected."));
	if (!values[1] || !values[2] || values[3])
		return (ft_error("Ambient Light missing/extra parameters."));
	scene->a.ratio = ft_atof(values[1]);
	if (scene->a.ratio < 0.0 || scene->a.ratio > 1.0)
		return (ft_error("Ambient ratio out of range."));
	scene->a.colour = parse_colour(values[2]);
	if (invalid_colour(&scene->a.colour))
		return (ERROR);
	return (0);
}

// creates the camera object if it is the first one to exits
// if any exists before, exits
// expects C  POINT[x,y,z]  horizontal_FOW(0-180˚)  orientation_vector(x,y,z)
int	fill_camera(t_scene *scene, char **values)
{
	scene->c_count++;
	if (scene->c_count > 1)
		return (ft_error("Dublicate Camera has been detected."));
	if (!values[1] || !values[2] || !values[3] || values[4])
		return (ft_error("Camera missing/extra parameters."));
	scene->c.point = parse_coord(values[1]);
	if (invalid_coord(&scene->c.point))
		return (ERROR);
	scene->c.vector = parse_coord(values[2]);
	if (invalid_coord(&scene->c.vector))
		return (ERROR);
	if (!is_vector_normalized(scene->c.vector))
	{
		if (!scene->c.vector.x && !scene->c.vector.y && !scene->c.vector.z)
			return (ft_error("Camera orientation vector cannot be (0,0,0)."));
		normalize(&scene->c.vector);
		printf("NOTE: Camera vector was normalized during execution.\n");
	}
	scene->c.view_degree = ft_atoi(values[3]);
	if (scene->c.view_degree < 0 || scene->c.view_degree > 180)
		return (ft_error("Camera field of view out of range."));
	return (0);
}

// creates a visual "sun" sphere at the light's position.
// this does NOT append the sphere to the scene. Store it manually.
t_sphere	*fill_lightsource_object(t_light light)
{
	t_sphere	*light_sphere;

	light_sphere = malloc(sizeof(t_sphere));
	if (!light_sphere)
	{
		ft_error("Memory allocation failed for light sphere.");
		return (NULL);
	}
	light_sphere->centre = light.lightpoint;
	light_sphere->diameter = 5;
	light_sphere->colour = light.colour;
	light_sphere->id = -42;
	light_sphere->next = NULL;
	return (light_sphere);
}

// creates the light object if it is the first one to exits
// if any exists before, exits
// expects L  POINT[x,y,z]  horizontal_FOW(0-180˚)  orientation_vector(x,y,z)
int	fill_light(t_scene *scene, char **values)
{
	scene->l_count++;
	if (scene->l_count > 1)
		return (ft_error("Dublicate Light has been detected."));
	if (!values[1] || !values[2] || !values[3] || values[4])
		return (ft_error("Light missing/extra parameters."));
	scene->l.lightpoint = parse_coord(values[1]);
	if (invalid_coord(&scene->l.lightpoint))
		return (ERROR);
	scene->l.brightness = ft_atof(values[2]);
	if (scene->l.brightness < 0.0 || scene->l.brightness > 1.0)
		return (ft_error("Light brightness out of range."));
	scene->l.colour = parse_colour(values[3]);
	if (invalid_colour(&scene->l.colour))
		return (ERROR);
	scene->light_sphere = fill_lightsource_object(scene->l);
	return (0);
}

// compares first identifier and creates objects accordingly 
int	identify_object(t_scene *scene, char *identifier, char **values)
{
	static int	id;

	if (!ft_strncmp(identifier, "A\0", 2))
		return (fill_ambient(scene, values));
	else if (!ft_strncmp(identifier, "C\0", 2))
		return (fill_camera(scene, values));
	else if (!ft_strncmp(identifier, "L\0", 2))
		return (fill_light(scene, values));
	else if (!ft_strncmp(identifier, "sp\0", 3))
		return (fill_sphere(scene, values, &id));
	else if (!ft_strncmp(identifier, "pl\0", 3))
		return (fill_plane(scene, values, &id));
	else if (!ft_strncmp(identifier, "cy\0", 3))
		return (fill_cylinder(scene, values, &id));
	return (ft_error("Unknown object type."));
}
