/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zchoo <zchoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/17 19:06:18 by ka-tan            #+#    #+#             */
/*   Updated: 2026/06/03 18:44:19 by zchoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	render_scene(t_scene *scene)
{
	(void)scene;
	ft_printf("Rendering scene...\n");
	// Render the scene using the mlx functions
	color_map_1(scene->mlx, WIDTH, HEIGHT);
	mlx_put_image_to_window(scene->mlx->mlx, scene->mlx->win, scene->mlx->img, 0, 0);
}

void	save_image(const char *filename, t_scene *scene)
{
	(void)scene;
	// mlx_xpm_to_image()
	ft_printf("Saving rendered image to \"%s\"\n", filename);
}

/* void	test(void)
{
	t_vec3	vec;

	ft_printf("Test function called\n");
	vec = vec3_init(1, 2, 3);
	ft_printf("vec3_init(1, 2, 3) = (%f, %f, %f)\n", vec.x, vec.y, vec.z);
	//test_vec3();
} */

void	test(void)
{
	t_scene	scene;
	char	*tokens[4];

	/* Happy path */
	tokens[0] = "A";
	tokens[1] = "0.2";
	tokens[2] = "255,128,0";
	tokens[3] = NULL;
	parse_ambient(tokens, &scene);
}

static void	dump_objects(t_object *obj)
{
	while (obj)
	{
		if (obj->type == SPHERE)
			ft_printf("  sp centre=(%f,%f,%f) r=%f\n", obj->shape.sp.centre.x,
				obj->shape.sp.centre.y, obj->shape.sp.centre.z,
				obj->shape.sp.radius);
		else if (obj->type == PLANE)
			ft_printf("  pl point=(%f,%f,%f)\n", obj->shape.pl.point.x,
				obj->shape.pl.point.y, obj->shape.pl.point.z);
		else
			ft_printf("  cy (stub)\n");
		obj = obj->next;
	}
}

void	init_mlx(t_mlx *mlx)
{
	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, WIDTH, HEIGHT, "miniRT");
	mlx->img = mlx_new_image(mlx->mlx, WIDTH, HEIGHT);
	mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bpp, &mlx->line_len,
			&mlx->endian);
}

static int	free_memory(t_mlx *mlx)
{
	if (!mlx)
		return (1);
	free(mlx);
	return (0);
}

int	close_window(t_mlx *mlx)
{
	ft_printf("Close hook triggered\n");
	mlx_destroy_image(mlx->mlx, mlx->img);
	mlx_clear_window(mlx->mlx, mlx->win);
	mlx_destroy_window(mlx->mlx, mlx->win);
	mlx_destroy_display(mlx->mlx);
	free_memory(mlx);
	exit(0);
	return (0);
}

int	key_hook(int keycode, void *param)
{
	ft_printf("Key pressed: %d/0x%x\n", keycode, keycode);
	if (keycode == XK_Escape)
		close_window((t_mlx *)param);
	return (0);
}

int	expose_hook(void* data)
{
	render_scene((t_scene *)data);
	ft_printf("Expose hook triggered\n");
	return (0);
}

int	loop_hook(t_mlx *mlx)
{
	(void)mlx;
	return (0);
}

int	main(int argc, char **argv)
{
	t_scene	scene;

	check_args(argc, argv);
	if (parse_scene(argv[1], &scene) == -1)
	{
		scene_free(&scene);
		return (1);
	}
	ft_printf("objects:\n");
	dump_objects(scene.objects);

	scene.mlx = malloc(sizeof(t_mlx));
	if (scene.mlx == NULL)
	{
		ft_putstr_fd("Error: Failed to allocate memory for mlx\n", 2);
		return (1);
	}
	init_mlx(scene.mlx);
	mlx_key_hook(scene.mlx->win, key_hook, scene.mlx);
	mlx_hook(scene.mlx->win, 17, 0, close_window, scene.mlx);
	mlx_expose_hook(scene.mlx->win, expose_hook, scene.mlx);
	mlx_string_put(scene.mlx->mlx, scene.mlx->win, 10, 10, 0xFFFFFF, "Hello, miniRT!");
	mlx_loop_hook(scene.mlx->mlx, loop_hook, scene.mlx);
	
	render_scene(&scene);
	
	mlx_loop(scene.mlx->mlx);
	scene_free(&scene);
	return (0);
}
