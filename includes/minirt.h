/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpiarova <zpiarova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 16:45:28 by yhusieva          #+#    #+#             */
/*   Updated: 2025/05/09 16:50:50 by zpiarova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <math.h>
# include <fcntl.h>
# include <float.h>
# include <ctype.h>
# include "../lib/libft/libft.h"
# include "../lib/MLX42/include/MLX42/MLX42.h"

/* ------------------------------ MACROS ----------------------------- */
# define WIDTH 800
# define HEIGHT 600
# define INT_ERROR INT_MIN
# define ERROR 1
# define SUCCESS 0
# define REFLECTION 30
# define ANGLE_RADIAN 0.2f
# define ZOOM 1
# define TRANSLATION 5
# define EPSILON 1e-6

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
	t_colour		colour;
	struct s_light	*next;
}					t_light;

typedef struct s_light_math
{
	t_coord			normal;
	t_coord			shadow_ray;
	t_coord			shadow_vector;
	t_coord			shadow_origin;
	float			max_length;
	t_coord			incident_l;
	float			scalar_nl;
	t_coord			incident_v;
	t_coord			reflected_vector;
	float			scalar_vr;
	float			reflectivity;
}					t_light_math;

/* ----------------------------- OBJECTS ------------------------------- */
typedef struct s_sphere
{
	int				id;
	t_coord			centre;
	float			diameter;
	t_colour		colour;
	struct s_sphere	*next;
}					t_sphere;

typedef struct s_plane
{
	int				id;
	t_coord			point;
	t_coord			vector;
	t_colour		colour;
	struct s_plane	*next;
}					t_plane;

typedef struct s_cylinder
{
	int					id;
	t_coord				centre;
	t_coord				vector;
	float				diameter;
	float				height;
	t_colour			colour;
	struct s_cylinder	*next;
}						t_cylinder;

/* ----------------------- MATH CALCULATIONS ------------------------------ */

typedef struct s_quadr_coef
{
	float			a;
	float			b;
	float			c;
	float			discriminant;
	float			t1;
	float			t2;
}					t_quadr_coef;

typedef struct s_matrix
{
	t_coord			right;
	t_coord			forward;
	t_coord			up;
	t_coord			translation;
}					t_matrix;

typedef struct s_inter
{
	t_coord			point;
	enum e_obj_t	type;
	t_colour		colour;
	void			*obj;
	float			distance;
	float			ld;
	int				id;
	struct s_inter	*next;
}					t_inter;

typedef struct s_roots
{
	float	t1;
	float	t2;
	float	t3;
	float	t4;
}					t_roots;

/* ------------------------ SCENE DESCRIPTION -------------------------- */

typedef struct s_scene
{
	t_ambient		a;
	t_camera		c;
	t_light			*l;
	t_sphere		*sp;
	t_plane			*pl;
	t_cylinder		*cy;
	t_sphere		*light_spheres;
	int				a_count;
	int				c_count;
	float			viewport_distance;
	float			viewport_width;
	float			viewport_height;
	t_matrix		tm;
	t_colour		bg;
}					t_scene;

typedef struct s_minirt
{
	mlx_t			*mlx;
	mlx_image_t		*img;
	int				img_width;
	int				img_height;
	t_scene			*scene;
	t_colour		**pixels;
	t_inter			***intersection;
}					t_minirt;

/* ------------------------------- FUNCTIONS ------------------------------ */

int			minirt_init(t_minirt *rt, t_scene *scene);
int			generate_image(t_minirt *minirt);

// RAY MATH
int			shoot_rays(t_minirt *minirt, t_scene *scene);
t_matrix	find_transformation_matrix(t_camera c);
float		get_viewport_width(float angle_deg, float distance);
float		get_viewport_height(float viewport_width);
double		scale(double num, double new_min, double new_max, double old_max);
void		find_roots(t_quadr_coef *qc);

// INTERSECTIONS
t_inter		*find_sphere_inters(t_coord ray, t_coord origin, t_sphere *sp);
t_inter		*find_plane_inters(t_coord ray, t_coord origin, t_plane *pl);
t_inter		*find_cylinder_inters(t_coord ray, t_coord origin, t_cylinder *cy);
void		merge_sort(t_inter **list_head);
void		set_id_colour_type(t_inter *i, int id, enum e_obj_t t, t_colour c);
t_inter		*make_inter(void *obj, float t, t_coord ray, t_coord origin);
t_inter		*return_object_inters(t_inter *in1, t_inter *in2);

// VECTOR MATH
float		get_dot_product(t_coord A, t_coord B);
t_coord		get_cross_product(t_coord A, t_coord B);
int			is_vector_normalized(t_coord v);
void		normalize(t_coord *N);
t_coord		make_vector(t_coord from, t_coord to);
t_coord		get_point_on_vector(t_coord C, t_coord v, float d);
bool		are_collinear(t_coord A, t_coord B);
t_coord		subtract_vectors(t_coord from, t_coord to);
t_coord		multiply_vector_by_constant(t_coord v, float n);
t_coord		move_point_by_vector(t_coord point, t_coord vector);
int			are_parallel(t_coord vector1, t_coord vector2);
t_coord		multiply_transpose(t_matrix R, t_coord v);
t_coord		add_vectors(t_coord v1, t_coord v2);
t_coord		rotate_vector_around_axis(t_coord v, t_coord axis, float angle);
float		get_two_points_distance(t_coord a, t_coord b);

// LIGHT
int			lighting(t_minirt *minirt);
int			is_in_shadow(t_scene *scene, t_light_math *light_inp, int curr_id);

// MOVEMENT
void		ft_hook(void *param);
void		resize_hook(int width, int height, void *param);
void		scroll_zoom(double xdelta, double ydelta, void *param);
void		move(t_minirt *minirt, t_coord direction, float translation);
void		rotate_x(t_minirt *minirt, t_coord *original_vector, float angle);
void		rotate_y(t_minirt *minirt, t_coord *original_vector, float angle);
void		rotate_z(t_minirt *minirt, t_coord *original_vector, float angle);

// PARSING
t_scene		*create_scene(char *filename);
void		init_scene(t_scene *scene);
char		**store_file_contents(char *filename);
t_coord		parse_coord(char *coord);
t_colour	parse_colour(char *clr);
int			invalid_coord(t_coord *coord);
int			invalid_colour(t_colour *clr);
int			check_file_format(char *filename);
int			fill_sphere(t_scene *scene, char **values, int *i);
void		append_sphere(t_sphere **sphere_list, t_sphere *new_sphere);
int			fill_plane(t_scene *scene, char **values, int *i);
int			fill_cylinder(t_scene *scene, char **values, int *i);
int			identify_object(t_scene *scene, char *identifier, char **values);

// UTILS
int32_t		ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a);
double		ft_atof(char *str);
int			ft_error(const char *msg);
t_coord		set_coord(float x, float y, float z);
t_colour	set_colour(int r, int b, int g, int a);
void		append_node(t_inter *new_node, t_inter **head);
int			is_valid_input(char **values);
char		*normalise_whitespace(char *str);
int			is_empty_line(char *line);
int			ft_is_space(char c);
int			dot_comma_limit(char *str, int *i, int *comma, int *has_dot);
int			is_numerical(char *str);

// ALLOCATE
t_colour	**allocate_pixels(int width, int height, t_colour background_color);
t_inter		***allocate_inter(int width, int height);

// FREE
void		cleanup(t_minirt *minirt);
void		free_arr(char **arr);
void		free_scene(t_scene *scene);
void		free_list(t_inter **lst, void (*del)(void *));
void		free_inter(t_inter ***section, int h, int w);
void		free_pixels(t_colour **p, int h);

// PRINT
void		print_controls(void);
void		print_scene(t_scene *scene);
void		print_coord(t_coord coord);
void		print_colour(t_colour colour);

#endif
