/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpiarova <zpiarova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 16:45:28 by yhusieva          #+#    #+#             */
/*   Updated: 2025/03/09 20:01:22 by zpiarova         ###   ########.fr       */
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
    float ratio; // [0.0, 1.0]
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
    t_colour colour; // bonus?
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

typedef struct s_cyliner
{
    t_coord centre;
    t_coord vector;
    float diameter;
    float height;
    t_colour colour;
    struct s_cyliner *next;
} t_cylinder;

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

// MATH
int transform_to_tl(char coordinate, float value);
float get_viewport_width(float angle_deg, float distance);
t_coord *get_viewport_coordinate();

// HOOKS
void ft_hook(void *param);

// PARSING
int parse_scene(t_minirt *minirt, char *rt_file);
t_scene *fill_scene(char **rows, int size);
int default_scene(t_scene *scene);
t_coord parse_coord(char *coord);
t_colour parse_colour(char *clr);
t_coord set_coord(float x, float y, float z);
t_colour set_colour(int r, int b, int g);
char	**get_lines(char *arg, int size);
int	count_rows(char *arg);
int valid_input(char **values);

// UTILS
void ft_error_mlx(void);
int ft_error(const char *msg);
void ft_free(char **arr, int size);
double ft_atof(const char *str);
int check_file_format(char *filename);

// TESTS - REMOVE AFTER DONE
void print_scene(t_scene *scene);
void create_test_sphere(t_sphere *sp);

#endif