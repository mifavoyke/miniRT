/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpiarova <zpiarova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 16:45:28 by yhusieva          #+#    #+#             */
/*   Updated: 2025/04/28 17:19:10 by zpiarova         ###   ########.fr       */
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

/* ------------------------------ MACROS ----------------------------- */
#define WIDTH 800
#define HEIGHT 600
#define INT_ERROR INT_MIN
#define ERROR 1
#define SUCCESS 0
#define MATTE 4
#define PLASTIC 30
#define GLASS 100
#define ANGLE_RADIAN 0.2
#define ZOOM 0.5
#define TRANSLATION 5

/* ------------------------ DATA STRUCTURES --------------------------- */
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

enum e_obj_t
{
	SPHERE,
	PLANE,
	CYLINDER,
	NO_OB
};

/* ------------------------- SCENE INFORMATION -------------------------- */
typedef struct s_ambient
{
	float			ratio;
	t_colour		colour;
}					t_ambient;

typedef struct s_camera
{
	t_coord			point;
	t_coord			vector;
	float			view_degree;
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
	t_coord			shadow_ray;
	t_coord			shadow_vector;
	t_coord shadow_origin;
	float max_length;
	t_coord			incident_l; // incident light vector
	float			scalar_nl; // cosine between the normal and incident light vector
	t_coord			incident_v; // incident vector starting from the camera (viewpoint) to P
	t_coord			reflected_vector;
	float			scalar_vr; // cosine between the viewpoint (camera) and reflection vector
	float			reflectivity;
}					t_light_math;

/* ----------------------------- OBJECTS ------------------------------- */
typedef struct s_sphere
{
	int id;
	t_coord			centre;
	float			diameter;
	t_colour		colour;
	struct s_sphere	*next;
}					t_sphere;

typedef struct s_plane
{
	int id;
	t_coord			point;
	t_coord			vector;
	t_colour		colour;
	struct s_plane	*next;
}					t_plane;

typedef struct s_cylinder
{
	int id;
	t_coord				centre;
	t_coord				vector;
	float				diameter;
	float				height;
	t_colour			colour;
	struct s_cylinder	*next;
}						t_cylinder;

/* ----------------------- MATH CALCULATIONS ------------------------------ */
typedef struct s_matrix
{
	t_coord			R;
	t_coord			F;
	t_coord			U;
	t_coord			Tr;
}					t_matrix;

typedef struct s_inter
{
	t_coord			point;
	enum e_obj_t	type;
	t_colour		colour;
	void			*obj;
	float			distance;
	int id;
	struct s_inter	*next;
}					t_inter;

/* ------------------------ SCENE DESCRIPTION -------------------------- */

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
	float			viewport_distance;
	float			viewport_width;
	float			viewport_height;
	t_colour		background;
}					t_scene;

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

/* ------------------------------- FUNCTIONS ------------------------------ */
// LIGHT
int lighting(t_minirt *minirt);
int is_in_shadow(t_minirt *minirt, t_light_math *light_inputs, int current_id);

// PIXELS
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
t_coord move_point_by_vector(t_coord point, t_coord vector);
t_coord add_vectors(t_coord v1, t_coord v2);

// MATH - basic.c
int equals(float a, float b, float deviation);
float get_discriminant(float a, float b, float c);
double scale(double num, double new_min, double new_max, double old_max);
int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a);

// MATH - math.c
float get_viewport_height(float viewport_width);
float get_viewport_width(float angle_deg, float distance);
float get_discriminant(float a, float b, float c);
t_coord make_vector(t_coord from, t_coord to);
t_coord get_point_on_vector(t_coord C, t_coord v, float d);
float get_viewport_width(float angle_deg, float distance);
int shoot_rays(t_minirt *minirt, t_scene *scene);
float get_plane_intersection_t(t_coord ray, t_coord cam_origin, t_plane *pl);

// MATH - intersections.c
t_inter *find_sphere_intersections(t_coord ray, t_camera cam, t_sphere *sp);
t_inter *find_plane_intersections(t_coord ray, t_camera cam, t_plane *pl);
t_inter *find_cylinder_intersections(t_coord ray, t_camera cam, t_cylinder *cy);

// HOOKS
void resize_hook(int width, int height, void* param);
void ft_hook(void *param);
void print_controls(void);
void scroll_zoom(double xdelta, double ydelta, void *param);
int generate_image(t_minirt *minirt);

// PARSING
void free_scene(t_scene *scene);
int	count_rows(int fd);
char	**get_file_data(int fd, int size);
t_scene	*create_scene(char *filename);
int fill_scene(t_scene *scene, char **file_rows);

int	count_rows(int fd);
char	**store_file_contents(char *filename);
char	**get_file_data(int fd, int size);

void	print_colour(t_colour colour);
void	print_coord(t_coord coord);

int identify_object(t_scene *scene, char *first_letter, char **values);
int fill_cylinder(t_scene *scene, char **values, int i);
int fill_plane(t_scene *scene, char **values, int i);
int fill_sphere(t_scene *scene, char **values, int i);

// UTILS
int check_file_format(char *filename);
int ft_error(const char *msg);
char *normalise_whitespace(char *str);
void free_arr(char **arr);
void print_arr(char **arr);
int ft_is_space(char c);
int	is_empty_line(char *line);
int is_valid_input(char **values);
int is_numerical(char *str);
double ft_atof(char *str);
void print_scene(t_scene *scene);
void append_node(t_inter *new_node, t_inter **head);
void print_list(t_inter *head, int x, int y);
void merge_sort(t_inter **list_head);
int minirt_init(t_minirt *minirt, t_scene *scene);
void	init_scene(t_scene *scene);


// UTILS
t_colour set_colour(int r, int b, int g, int a);
t_coord set_coord(float x, float y, float z);
t_coord parse_coord(char *coord);
t_colour parse_colour(char *clr);
int32_t  ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a);
int invalid_coord(t_coord *coord);
int invalid_colour(t_colour *clr);
t_inter ***allocate_inter(int width, int height);
t_colour **allocate_pixels(int width, int height, t_colour background_colour);
void free_arr(char **arr);
void free_scene(t_scene *scene);
void free_pixels(t_colour **p, int h);
void free_inter(t_inter ***section, int h, int w);
void	free_list(t_inter **lst, void (*del)(void *));
void	cleanup(t_minirt *minirt);
void print_controls(void);


// TESTS - REMOVE AFTER DONE
void print_scene(t_scene *scene);
void print_light_math_inputs(t_light_math *inputs);
void print_coord(t_coord coord);
void print_camera(t_camera *c);
void draw_shadow_rays(t_minirt *minirt);
void draw_line(t_minirt *minirt, t_coord start, t_coord end, t_colour color);
void print_light(t_light *l);


// -------------

// PARSING
void init_scene(t_scene *scene);
void free_scene(t_scene *scene);
int fill_scene(t_scene *scene, char **file_rows);

char	**store_file_contents(char *filename);
char	**get_file_data(int fd, int size);


int identify_object(t_scene *scene, char *first_letter, char **values);
int fill_cylinder(t_scene *scene, char **values, int i);
int fill_plane(t_scene *scene, char **values, int i);
int fill_sphere(t_scene *scene, char **values, int i);

// MATH
float get_viewport_width(float angle_deg, float distance);
float get_viewport_height(float viewport_width);

// MATH - vector.c
void normalize(t_coord *N);
int is_vector_normalized(t_coord v);


// UTILS
int check_file_format(char *filename);
int ft_error(const char *msg);
char *normalise_whitespace(char *str);
void free_arr(char **arr);
void print_arr(char **arr);
int ft_is_space(char c);
int	is_empty_line(char *line);
int is_valid_input(char **values);
int is_numerical(char *str);
double ft_atof(char *str);
void print_scene(t_scene *scene);


t_colour set_colour(int r, int b, int g, int a);
t_coord set_coord(float x, float y, float z);
t_coord parse_coord(char *coord);
t_colour parse_colour(char *clr);
int32_t  ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a);
int invalid_coord(t_coord *coord);
int invalid_colour(t_colour *clr);

#endif
