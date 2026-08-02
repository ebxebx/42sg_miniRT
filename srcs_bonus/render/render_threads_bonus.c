/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_threads_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zchoo <zchoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/02 20:59:11 by zchoo             #+#    #+#             */
/*   Updated: 2026/08/02 21:00:06 by zchoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"
#include <unistd.h>

static void	render_pixel(t_scene *scene, int x, int y)
{
	t_ray	ray;
	t_hit	hit;
	t_vec3	color;

	if (scene->show_fisheye)
		ray = camera_ray_fisheye(scene, x, y);
	else
		ray = camera_ray(scene, x, y);
	if (!vec3_equal(ray.direction, vec3_zero()) && hit_scene(scene, ray,
			INFINITY, &hit))
		color = shade_hit(scene, &hit);
	else
		color = vec3_zero();
	my_mlx_pixel_put(scene->mlx, x, y, pack_color(color));
}

static void	*render_rows(void *arg)
{
	t_render_job	*job;
	int				x;
	int				y;

	job = (t_render_job *)arg;
	y = job->y_start;
	while (y < job->y_end)
	{
		x = 0;
		while (x < WIDTH)
		{
			render_pixel(job->scene, x, y);
			x++;
		}
		y++;
	}
	return (NULL);
}

static int	get_thread_count(void)
{
	long	count;

	count = sysconf(_SC_NPROCESSORS_ONLN);
	if (count < 1)
		count = 1;
	if (count > MAX_RENDER_THREADS)
		count = MAX_RENDER_THREADS;
	if (count > HEIGHT)
		count = HEIGHT;
	return ((int)count);
}

static void	start_workers(t_render_pool *pool, t_scene *scene)
{
	int	i;

	i = 0;
	while (i < pool->count)
	{
		pool->jobs[i].scene = scene;
		pool->jobs[i].y_start = i * HEIGHT / pool->count;
		pool->jobs[i].y_end = (i + 1) * HEIGHT / pool->count;
		pool->created[i] = !pthread_create(pool->threads + i, NULL, render_rows,
				pool->jobs + i);
		if (!pool->created[i])
			render_rows(&pool->jobs[i]);
		i++;
	}
}

void	render_multithreaded(t_scene *scene)
{
	t_render_pool	pool;
	int				i;

	pool.count = get_thread_count();
	start_workers(&pool, scene);
	i = 0;
	while (i < pool.count)
	{
		if (pool.created[i])
			pthread_join(pool.threads[i], NULL);
		i++;
	}
}
