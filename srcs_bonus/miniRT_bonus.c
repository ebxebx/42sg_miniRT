/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zchoo <zchoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 19:32:46 by zchoo             #+#    #+#             */
/*   Updated: 2026/08/02 19:42:55 by zchoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

// Validate the CLI invocation: exactly one argument, ending in ".rt".
// Exits the program immediately on a bad usage.
static void	check_args(int argc, char **argv)
{
	char	*ext;

	if (argc != 2)
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

// Set up MLX (window/image), wire up input/render hooks, draw the first
// frame, then hand control to the MLX event loop until the window closes
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

// Entry point: validate args, parse the .rt scene file, then run it
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
