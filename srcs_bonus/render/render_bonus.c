/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zchoo <zchoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 19:40:42 by zchoo             #+#    #+#             */
/*   Updated: 2026/08/02 19:42:16 by zchoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

static void	build_camera_ray(t_scene *scene, int x, int y, t_ray *ray)
{
	if (scene->show_fisheye)
		*ray = camera_ray_fisheye(scene, x, y);
	else
		*ray = camera_ray(scene, x, y);
}

// Trace one ray per pixel across the whole image, shade whatever it hits
// (or paint black on a miss), then blit the finished image to the window
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
			build_camera_ray(scene, x, y, &ray);
			if ((vec3_equal(ray.direction, vec3_zero()) == 0)
				&& hit_scene(scene, ray, INFINITY, &hit))
				color = shade_hit(scene, &hit);
			else
				color = vec3_zero();
			my_mlx_pixel_put(scene->mlx, x, y, pack_color(color));
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(scene->mlx->mlx, scene->mlx->win, scene->mlx->img,
		0, 0);
}

// Set up the MLX connection, window, and backing image used for rendering
int	init_mlx(t_mlx *mlx)
{
	mlx->mlx = mlx_init();
	if (!mlx->mlx)
		return (1);
	mlx->win = mlx_new_window(mlx->mlx, WIDTH, HEIGHT, "miniRT");
	if (!mlx->win)
		return (mlx_destroy_display(mlx->mlx), free(mlx->mlx), 1);
	mlx->img = mlx_new_image(mlx->mlx, WIDTH, HEIGHT);
	if (!mlx->img)
	{
		mlx_destroy_window(mlx->mlx, mlx->win);
		mlx_destroy_display(mlx->mlx);
		return (free(mlx->mlx), 1);
	}
	mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bpp, &mlx->line_len,
			&mlx->endian);
	if (!mlx->addr)
	{
		mlx_destroy_image(mlx->mlx, mlx->img);
		mlx_destroy_window(mlx->mlx, mlx->win);
		mlx_destroy_display(mlx->mlx);
		return (free(mlx->mlx), 1);
	}
	return (0);
}

// Free an allocated pointer, guarding against a NULL pointer
static void	free_ptr(void *p)
{
	if (p)
		free(p);
}

// is the program's sole exit point, triggered by Escape or a window close
// Note:
// mlx_destroy_display() only calls XCloseDisplay(); it never frees
// the t_xvar struct that mlx_init() malloc'd and returned as this
// opaque handle, so we must free it ourselves.
int	close_window(t_scene *scene)
{
	if (scene->mlx)
	{
		mlx_destroy_image(scene->mlx->mlx, scene->mlx->img);
		mlx_clear_window(scene->mlx->mlx, scene->mlx->win);
		mlx_destroy_window(scene->mlx->mlx, scene->mlx->win);
		mlx_destroy_display(scene->mlx->mlx);
		free_ptr(scene->mlx->mlx);
		free_ptr(scene->mlx);
		scene->mlx = NULL;
	}
	scene_free(scene);
	exit(0);
	return (0);
}
