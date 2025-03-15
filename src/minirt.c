#include "../includes/minirt.h"

int minirt_init(t_minirt *minirt)
{
	minirt->img_width = 1920;
	minirt->img_height = 1080;
	// mlx_set_setting(MLX_MAXIMIZED, true);
	minirt->mlx = mlx_init(WIDTH, HEIGHT, "miniRT", true);
	if (!minirt->mlx)
		return (1);
	minirt->img = mlx_new_image(minirt->mlx, minirt->img_width, minirt->img_height);
	if (!minirt->img || (mlx_image_to_window(minirt->mlx, minirt->img, 0, 0) < 0))
		return (1);
	return (0);
}

int32_t main(int argc, char *argv[])
{
	t_minirt minirt;

	if (argc != 2)
		return (ft_error("Usage: ./miniRT [scene].rt"));
	if (check_file_format(argv[1]))
		return (ft_error("Wrong scene format. Expected .rt file."));
	if (parse_scene(&minirt, argv[1]))
		return (1);
	if (minirt_init(&minirt))
		return (ft_error(mlx_strerror(mlx_errno)));

	minirt.pixels = allocate_pixels(minirt.img_width, minirt.img_height);
	if (!minirt.pixels)
		return (1);
	init_pixels(&minirt);
	print_scene(minirt.scene);
	brighten_up(minirt.scene); // apply ambience

	minirt.scene->viewport = set_viewport_plane(*minirt.scene);
	shoot_rays(&minirt, minirt.img, minirt.scene);

	// print_pixels(&minirt);
	render_pixels(&minirt);

	mlx_loop_hook(minirt.mlx, ft_hook, (void *)&minirt);
	mlx_loop(minirt.mlx);

	free_scene(minirt.scene);
	free_pixels(minirt.pixels, HEIGHT);
	mlx_delete_image(minirt.mlx, minirt.img);
	mlx_terminate(minirt.mlx);
	return (0);
}
