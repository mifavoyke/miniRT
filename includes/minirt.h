/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpiarova <zpiarova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 16:45:28 by yhusieva          #+#    #+#             */
/*   Updated: 2025/04/15 11:52:48 by zpiarova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <fcntl.h>
#include <float.h>
#include <ctype.h>
#include "../lib/libft/libft.h"
#include "../lib/MLX42/include/MLX42/MLX42.h"
#define WIDTH 500
#define HEIGHT 500
#define INT_ERROR INT_MIN
#define ERROR 1
#define SUCCESS 0
#define MATTE 4
#define PLASTIC 30
#define GLASS 100
#define TRANSLATION 10
#define TRANSLATION_NORM 0.2
#define EPSILON 1e-6

typedef struct s_colour
{
	int				r;
	int				g;
	int				b;
	int				a;
}					t_colour;

typedef struct s_coord
{
	float			x;
	float			y;
	float			z;
}					t_coord;

typedef struct s_ambient
{
	float			ratio;
	t_colour		colour;
}					t_ambient;

typedef struct s_camera
{
	t_coord			point;
	t_coord			vector;
	int				view_degree;
}					t_camera;

typedef struct s_light
{
	t_coord			lightpoint;
	float			brightness;
	t_colour		colour; // bonus
}					t_light;

typedef struct s_light_math
{
	t_coord			normal; // calculated differently for every object
	t_coord			actual_v_to_l;
	t_coord			incident_l; // incident light vector
	float			scalar_nl; // cosine between the normal and incident light vector
	t_coord			incident_v; // incident vector starting from the camera (viewpoint) to P
	t_coord			reflected_vector;
	float			scalar_vr; // cosine between the viewpoint (camera) and reflection vector
	float			reflectivity;
}					t_light_math;

typedef struct s_sphere
{
	t_coord			centre;
	float			diameter;
	t_colour		colour;
	struct s_sphere	*next;
}					t_sphere;

typedef struct s_plane
{
	t_coord			point;
	t_coord			vector;
	t_colour		colour;
	struct s_plane	*next;
}					t_plane;

typedef struct s_cylinder
{
	t_coord				centre;
	t_coord				vector;
	float				diameter;
	float				height;
	t_colour			colour;
	struct s_cylinder	*next;
}						t_cylinder;

typedef struct s_matrix
{
	t_coord			R;
	t_coord			F;
	t_coord			U;
	t_coord			Tr;
}					t_matrix;

typedef struct s_viewport
{
	float			d;
	float			viewport_width;
	float			viewport_height;
	t_coord			viewport_centre;
}					t_viewport;

typedef struct s_scene
{
	t_ambient		a;
	t_camera		c;
	t_light			l;
	t_sphere		*sp;
	t_plane			*pl;
	t_cylinder		*cy;
	int				a_count;
	int				c_count;
	int				l_count;
	int				sp_count;
	int				pl_count;
	int				cy_count;
	t_viewport		*viewport;
	t_colour		background;
}					t_scene;

enum e_obj_t
{
	SPHERE,   // 0
	PLANE,    // 1
	CYLINDER, // 2
	NO_OB
};

typedef struct s_inter
{
	t_coord			point;
	enum e_obj_t	type;
	t_colour		colour;
	void			*obj;
	float			distance;
	float			dist_to_light; // I need - yeva
	struct s_inter	*next;
}					t_inter;

typedef struct s_minirt
{
	mlx_t           *mlx;
	mlx_image_t     *img;
	int             img_width;
	int             img_height;
	t_scene         *scene;
	t_colour        **pixels;
	t_inter         ***intersection;
}					t_minirt;

// LIGHT
int lighting(t_minirt *minirt);

// PIXELS
void init_pixels(t_minirt *minirt);
void render_pixels(t_minirt *minirt);

// MATH - vector.c
float get_dot_product(t_coord A, t_coord B);
int is_vector_normalized(t_coord v);
t_coord make_vector(t_coord from, t_coord to);
t_coord get_point_on_vector(t_coord C, t_coord v, float d);
bool are_collinear(t_coord A, t_coord B);
t_coord get_cross_product(t_coord A, t_coord B);
void normalize(t_coord *N);
t_coord multiply_vector_by_constant(t_coord v, float n);
t_coord subtract_vectors(t_coord from, t_coord to);

// MATH - basic.c
int equals(float a, float b, float deviation);
float get_discriminant(float a, float b, float c);
double scale(double num, double new_min, double new_max, double old_max);
int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a);

// MATH - math.c
t_viewport *set_viewport_plane(t_scene scene);
float get_discriminant(float a, float b, float c);
t_coord make_vector(t_coord from, t_coord to);
t_coord get_point_on_vector(t_coord C, t_coord v, float d);
float get_viewport_width(float angle_deg, float distance);
t_coord get_viewport_ray(t_scene *scene, t_matrix m, int x, int y);
int shoot_rays(t_minirt *minirt, t_scene *scene);

// MATH - intersections.c
t_inter *find_sphere_intersections(t_coord ray, t_camera cam, t_sphere *sp, t_coord lightpoint);
t_inter *find_plane_intersections(t_coord ray, t_camera cam, t_plane *pl, t_coord lightpoint);
t_inter *find_cylinder_intersections(t_coord ray, t_camera cam, t_cylinder *cy);

// HOOKS
void ft_hook(void *param);
void generate_image(t_minirt *minirt);

// PARSING
int parse_scene(t_minirt *minirt, char *rt_file);
int identify_objects(t_scene *scene, char *first_letter, char **values);
int valid_input(char **values);
t_coord parse_coord(char *coord);
t_colour parse_colour(char *clr);
t_coord set_coord(float x, float y, float z);
t_colour set_colour(int r, int b, int g, int a);
int valid_coord(t_coord *coord);
int valid_colour(t_colour *clr);
char **get_lines(char *arg, int size);
int count_rows(char *arg);
int fill_sphere(t_scene *scene, char **values);

// UTILS
int ft_error(const char *msg);
double ft_atof(char *str);
int check_file_format(char *filename);

// ALLOCATE
t_inter ***allocate_inter(int width, int height);
t_colour **allocate_pixels(int width, int height);

// FREE
void free_arr(char **arr);
void free_scene(t_scene *scene);
void free_pixels(t_colour **p, int h);
void free_inter(t_inter ***section, int h, int w);


// TESTS - REMOVE AFTER DONE
void print_scene(t_scene *scene);
void print_light_math_inputs(t_light_math *inputs);
void print_list(t_inter *head, int x, int y);
void print_intersections(t_inter ***head, int w, int h);
void print_coord(t_coord coord);
void print_camera(t_camera *c);

#endif
