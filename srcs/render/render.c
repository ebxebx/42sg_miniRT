#include "miniRT.h"

void	render_scene(t_scene *scene)
{
	int		x;
	int		y;
	t_ray	ray;
	t_hit	hit;
	t_vec3	color;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			ray = camera_ray(scene, x, y);
			if (hit_scene(scene, ray, INFINITY, &hit))
				color = shade_hit(scene, &hit);
			else
				color = vec3_init(0.0, 0.0, 0.0);
			my_mlx_pixel_put(scene->mlx, x, y, pack_color(color));
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(scene->mlx->mlx, scene->mlx->win,
		scene->mlx->img, 0, 0);
}

int	init_mlx(t_mlx *mlx)
{
	mlx->mlx = mlx_init();
	if (!mlx->mlx)
		return (1);
	mlx->win = mlx_new_window(mlx->mlx, WIDTH, HEIGHT, "miniRT");
	if (!mlx->win)
		return (1);
	mlx->img = mlx_new_image(mlx->mlx, WIDTH, HEIGHT);
	if (!mlx->img)
		return (1);
	mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bpp, &mlx->line_len,
			&mlx->endian);
	if (!mlx->addr)
		return (1);
	return (0);
}

static int	free_memory(t_mlx *mlx)
{
	if (!mlx)
		return (1);
	free(mlx);
	return (0);
}

int	close_window(t_scene *scene)
{
	if (scene->mlx)
	{
		mlx_destroy_image(scene->mlx->mlx, scene->mlx->img);
		mlx_clear_window(scene->mlx->mlx, scene->mlx->win);
		mlx_destroy_window(scene->mlx->mlx, scene->mlx->win);
		mlx_destroy_display(scene->mlx->mlx);
		free_memory(scene->mlx->mlx);
		free_memory(scene->mlx);
		scene->mlx = NULL;
	}
	free_axes(scene->axes);
	scene_free(scene);
	exit(0);
	return (0);
}
