#include "../includes/minirt.h"

// Final Color = Object Color + (Ambient Light Color * Ambient Ratio)
t_colour apply_ambience(t_colour *obj_clr, t_colour *amb_clr, float lighting_ratio)
{
    t_colour result_clr;

    result_clr.r = obj_clr->r + (amb_clr->r * lighting_ratio);
    if (result_clr.r > 255)
        result_clr.r = 255;
    result_clr.g = obj_clr->g + (amb_clr->g * lighting_ratio);
    if (result_clr.g > 255)
        result_clr.g = 255;
    result_clr.b = obj_clr->b + (amb_clr->b * lighting_ratio);
    if (result_clr.b > 255)
        result_clr.b = 255;
    result_clr.a = 255;
    return (result_clr);
}

void brighten_up(t_scene *scene)
{
    t_sphere *tmp_sp;
    t_plane *tmp_pl;
    t_cylinder *tmp_cy;

    if (scene->sp)
    {
        tmp_sp = scene->sp;
        while (tmp_sp)
        {
            tmp_sp->colour = apply_ambience(&tmp_sp->colour, &scene->a.colour, scene->a.ratio);
            tmp_sp = tmp_sp->next;
        }
    }
    if (scene->pl)
    {
        tmp_pl = scene->pl;
        while (tmp_pl)
        {
            tmp_pl->colour = apply_ambience(&tmp_pl->colour, &scene->a.colour, scene->a.ratio);
            tmp_pl = tmp_pl->next;
        }
    }
    if (scene->cy)
    {
        tmp_cy = scene->cy;
        while (tmp_cy)
        {
            tmp_cy->colour = apply_ambience(&tmp_cy->colour, &scene->a.colour, scene->a.ratio);
            tmp_cy = tmp_cy->next;
        }
    }
}
