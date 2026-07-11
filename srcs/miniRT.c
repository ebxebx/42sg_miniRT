#include "miniRT.h"

static void	check_args(int argc, char **argv)
{
	char	*ext;

	if (argc < 2)
	{
		ft_putstr_fd("Error: Usage: ./miniRT <scene_file.rt>\n", 2);
		exit(1);
	}
	ext = ft_strrchr(argv[1], '.');
	if (!ext || ext == argv[1] || ext[-1] == '/' || ft_strcmp(ext, ".rt") != 0)
	{
		ft_putstr_fd("Error: Expected .rt file\n", 2);
		exit(1);
	}
}

static int	run_scene(t_scene *scene)
{
	scene->mlx = malloc(sizeof(t_mlx));
	if (scene->mlx == NULL)
	{
		ft_putstr_fd("Error: Failed to allocate memory for mlx\n", 2);
		return (1);
	}
	if (init_mlx(scene->mlx))
	{
		ft_putstr_fd("Error: Failed to initialize mlx\n", 2);
		free(scene->mlx);
		scene->mlx = NULL;
		return (1);
	}
	init_axes(scene);
	mlx_key_hook(scene->mlx->win, key_hook, scene);
	mlx_hook(scene->mlx->win, 17, 0, close_window, scene);
	mlx_expose_hook(scene->mlx->win, expose_hook, scene);
	mlx_loop_hook(scene->mlx->mlx, loop_hook, scene->mlx);
	render_scene(scene);
	mlx_loop(scene->mlx->mlx);
	return (0);
}

int	main(int argc, char **argv)
{
	t_scene	scene;

	check_args(argc, argv);
	if (parse_scene(argv[1], &scene) == -1 || run_scene(&scene))
	{
		scene_free(&scene);
		return (1);
	}
	scene_free(&scene);
	return (0);
}
