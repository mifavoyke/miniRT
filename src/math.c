/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpiarova <zpiarova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 15:24:04 by zpiarova          #+#    #+#             */
/*   Updated: 2025/03/09 20:46:00 by zpiarova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

// gets a scalar number from 2 vectors
// dot product of a vector with itself is its length
float dot_product(t_coord A, t_coord B)
{
    return (A.x * B.x + A.y * B.y + A.z  + B.z);
}

// self explanatory
// if D > 0 --> 2 roots (the ray enters and exits - 2 spots)
//    D = 0 --> 1 root (touches the surface)
//    D < 0 --> no roots (does not intersect)
float get_discriminant(float a, float b, float c)
{
    return (pow(b, 2) - 4 * a * c);
}

// makes a vector from point A to point B
t_coord make_vector(t_coord from, t_coord to)
{
    t_coord vector;

    vector.x = to.x - from.x;
    vector.y = to.y - from.y;
    vector.z = to.z - from.z;
    return (vector);
}

// linear interpolation function = maps/scales points proportionate and
// linearly to other points to keep the proportions but scaled in/out
double	scale(double num, double new_min, double new_max, double old_max)
{
	return ((new_max - new_min) * (num) / ((old_max)) + new_min);
}

// change coordinates top-left(TL) to center(C) system 
// TLx=ScreenWidth/2+Cx
// TLy=SceenHeight/2−Cy
int transform_to_tl(char coordinate, float value)
{
    if (coordinate == 'x')
        return (WIDTH / 2 + value);
    if (coordinate == 'y')
        return (HEIGHT / 2 - value);
    return (0);
}

// calculates the distance of the camera from the viewport plane (representing screen)
float get_viewport_width(float angle_deg, float distance)
{
    float   viewport_width;
    float   angle_rad;
    
    // Convert angle to radians
    angle_rad = angle_deg / 2 * M_PI / 180.0;
    viewport_width = 2 * (tan(angle_rad) / distance);
    return (viewport_width);
}

// it is calculated based on viewport width and to keep the ratio of screen width:height
float get_viewport_height(float viewport_width)
{
    return (viewport_width * HEIGHT / WIDTH);
}

// mapping screen pixel coordinate to a coordinate in the scene, mapped to the viewport size
t_coord *get_viewport_coordinate()
{
    t_coord *V;

    V = NULL;
    float viewport_width = get_viewport_width(60.0, 1.0); // TODO: maybe the distance d must be calculated, for now it is 1
    float viewport_height = get_viewport_height(viewport_width);
    
    printf("%f\n", viewport_width);
    printf("%f\n",  viewport_height);
    
    // Vx = Cx * Vw / Cw
    // Vy = Cy * Vh / Ch
    
    return (V);  
}

/*
// calculates the intersection of a sphere with the ray
// @param V is the pixel
t_coord sphere_intersection(t_coord *V, t_camera *C, t_sphere *sp)
{
    t_coord r;
    t_coord q;
    
    float a;
    float b;
    float c;
    
    float t1;
    float t2;
    float discriminant;
    
    r = make_vector(C->viewpoint, *V); // r = V - C --> vector in the direction from the camera to the viewpoint coordinate corresponding to a pixel in the screen 
    q = make_vector(C->viewpoint, sp->centre);  // q = C - S --> vector in the direction of the camera and the sphere centre

    a = dot_product(r, r);
    b = 2 * (dot_product(q, r));
    c = dot_product(q, q) - sp->diameter / 2;
    
    // this maybe has to be changed, what if the one where  we use + sqrt(D) is not root but the - sqrt(D) is the root
    discriminant = get_discriminant(a, b, c);
    if (discriminant >= 0)
        t1 = (-b + sqrt(discriminant)) / (2 * a);
    if (discriminant > 0)
        t2 = (-b - sqrt(discriminant)) / (2 * a);
    
    
        // dosad the t variable value that we now know to the equation P = C + t*(V - C);
    return (*V); // TODO: for now we return V, but not correct, jujst to shut up the errors 
}

int shoot_rays(t_scene *scene)
{
    int     x;
    int     y;
    t_coord viewport_point;
    t_coord ray;
    t_coord intersection;

    x = 0;
    y = 0;
    
    while (y < HEIGHT)
    {
        while (x < WIDTH)
        {
            viewport_point = get_viewport_coordinate();
            intersection = sphere_intersection(&viewport_point, &scene->c, scene->sp);
        }
        
    }
    
}
*/