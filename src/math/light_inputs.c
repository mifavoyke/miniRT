#include "../../includes/minirt.h"

// calculates the closest point on the cylinder axis and finds the vector from
// that closest point on the axis to the intersection point
static t_coord	calculate_cylider_normal(t_cylinder *cy, t_coord intersection_p)
{
	t_coord	closest_axis_point;
	t_coord	normal;
	int		t;

	t = dot(make_vector(cy->centre, intersection_p), cy->axis);
	closest_axis_point = get_point_on_vector(cy->centre, cy->axis, t);
	normal = make_vector(closest_axis_point, intersection_p);
	return (normal);
}

static t_coord	get_surface_normal(t_inter *intersection)
{
	t_sphere	*sp;
	t_plane		*pl;
	t_cylinder	*cy;

	if (intersection->type == SPHERE)
	{
		sp = (t_sphere *)intersection->obj;
		return (make_vector(sp->centre, intersection->point));
	}
	else if (intersection->type == PLANE)
	{
		pl = (t_plane *)intersection->obj;
		return (set_coord(pl->vector.x, pl->vector.y, pl->vector.z));
	}
	else if (intersection->type == CYLINDER)
	{
		cy = (t_cylinder *)intersection->obj;
		if (cy->axis.z == 1 || cy->axis.z == -1)
			return (make_vector(cy->centre, intersection->point));
		else
			return (calculate_cylider_normal(cy, intersection->point));
	}
	return (set_coord(0, 0, 0));
}

void	init_inputs(t_inter *intersection,
	t_light_math *vars, t_coord lightpoint, t_coord viewpoint)
{
	t_coord	offset;

	vars->normal = get_surface_normal(intersection);
	normalize(&vars->normal);
	vars->shadow_ray = make_vector(intersection->point, lightpoint);
	vars->max_length = sqrtf(dot(vars->shadow_ray, vars->shadow_ray));
	normalize(&vars->shadow_ray);
	offset = mult_vector_by_c(vars->shadow_ray, EPS);
	vars->shadow_origin = move_point_by_vector(intersection->point, offset);
	vars->incident_l = make_vector(intersection->point, lightpoint);
	normalize(&vars->incident_l);
	vars->scalar_nl = dot(vars->incident_l, vars->normal);
	vars->incident_v = make_vector(viewpoint, intersection->point);
	normalize(&vars->incident_v);
	vars->reflectivity = 0.0f;
}
