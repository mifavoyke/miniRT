/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpiarova <zpiarova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 16:45:28 by yhusieva          #+#    #+#             */
/*   Updated: 2025/03/13 17:43:14 by zpiarova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
#define MINIRT_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <fcntl.h>
#include <float.h>
#include <ctype.h>
#include "../lib/libft/libft.h"
#include "../lib/MLX42/include/MLX42/MLX42.h"
#define WIDTH 600
#define HEIGHT 400
#define INT_ERROR INT_MIN

typedef struct s_colour
{
    int r;
    int g;
    int b;
} t_colour;

typedef struct s_coord
{
    float x;
    float y;
    float z;
} t_coord;

typedef struct s_ambient
{
    float ratio;
    t_colour colour;
} t_ambient;

typedef struct s_camera
{
    t_coord viewpoint;
    t_coord vector;
    int view_degree;
} t_camera;

typedef struct s_light
{
    t_coord lightpoint;
    float brightness;
    t_colour colour; // bonus
} t_light;

typedef struct s_sphere
{
    t_coord centre;
    float diameter;
    t_colour colour;
    struct s_sphere *next;
} t_sphere;

typedef struct s_plane
{
    t_coord point;
    t_coord vector;
    t_colour colour;
    struct s_plane *next;
} t_plane;

typedef struct s_cylinder
{
    t_coord centre;
    t_coord vector;
    float diameter;
    float height;
    t_colour colour;
    struct s_cylinder *next;
} t_cylinder;

typedef struct s_matrix
{
    t_coord R;
    t_coord F;
    t_coord U;
    t_coord Tr;
}               t_matrix;

typedef struct s_viewport
{
    float d;
    float viewport_width;
	float viewport_height;
	t_coord viewport_centre;
}   t_viewport;

typedef struct s_scene
{
    t_ambient a;
    t_camera c;
    t_light l;
    t_sphere *sp;
    t_plane *pl;
    t_cylinder *cy;
    int a_count;
    int c_count;
    int l_count;
    int sp_count;
    int pl_count;
    int cy_count;
    t_viewport *viewport;
} t_scene;

typedef struct s_minirt
{
    mlx_t *mlx;
    mlx_image_t *img;
    int img_width;
    int img_height;
    t_scene *scene;
} t_minirt;

// MAIN

// MATH - vector.c
float get_dot_product(t_coord A, t_coord B);
int is_vector_normalized(t_coord v);
t_coord make_vector(t_coord from, t_coord to);
t_coord get_point_on_vector(t_coord C, t_coord v, float d);
bool are_collinear(t_coord A, t_coord B);
t_coord get_cross_product(t_coord A, t_coord B);
void normalize(t_coord *N);

// MATH - basic.c
int equals(float a, float b, float deviation);
float get_discriminant(float a, float b, float c);
double	scale(double num, double new_min, double new_max, double old_max);

//MATH - math.c
t_viewport *set_viewport_plane(t_scene scene);
float get_discriminant(float a, float b, float c);
t_coord make_vector(t_coord from, t_coord to);
t_coord get_point_on_vector(t_coord C, t_coord v, float d);
float get_viewport_width(float angle_deg, float distance);
t_coord get_viewport_ray(t_scene *scene, t_matrix m, int x, int y);
int shoot_rays(mlx_image_t *image, t_scene *scene);

// MATH - intersections.c
int sphere_intersection(t_coord ray, t_camera cam, t_sphere *sp);

// HOOKS
void ft_hook(void *param);

// PARSING
int parse_scene(t_minirt *minirt, char *rt_file);
int identify_objects(t_scene *scene, char *first_letter, char **values);
int valid_input(char **values);

t_coord parse_coord(char *coord);
t_colour parse_colour(char *clr);
t_coord set_coord(float x, float y, float z);
t_colour set_colour(int r, int b, int g);;
int valid_coord(t_coord *coord);
int valid_colour(t_colour *clr);
char	**get_lines(char *arg, int size);
int	count_rows(char *arg);

// UTILS
int ft_error(const char *msg);
void ft_free(char **arr);
void free_scene(t_scene *scene);
double ft_atof(const char *str);
int check_file_format(char *filename);

// TESTS - REMOVE AFTER DONE
void print_scene(t_scene *scene);

#endif
