#include "../includes/minirt.h"

void ft_hook(void *param)
{
    const t_minirt *minirt;

    minirt = param;
    if (mlx_is_key_down(minirt->mlx, MLX_KEY_ESCAPE))
        mlx_close_window(minirt->mlx);
}
