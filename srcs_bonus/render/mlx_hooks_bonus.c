/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hooks_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zchoo <zchoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 19:40:57 by zchoo             #+#    #+#             */
/*   Updated: 2026/08/02 19:12:02 by zchoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

#define ROTATE_STEP_DEG 5.0
#define PAN_STEP 0.5
#define ZOOM_STEP 5.0

static void	handle_camera(int keycode, t_scene *scene)
{
	double	step;

	step = degrees_to_radians(ROTATE_STEP_DEG);
	if (keycode == XK_Left)
		rotate_camera(&scene->camera, step, 0);
	else if (keycode == XK_Right)
		rotate_camera(&scene->camera, -step, 0);
	else if (keycode == XK_Up)
		rotate_camera(&scene->camera, 0, step);
	else if (keycode == XK_Down)
		rotate_camera(&scene->camera, 0, -step);
	else if (keycode == XK_j)
		pan_camera(&scene->camera, -PAN_STEP, 0);
	else if (keycode == XK_l)
		pan_camera(&scene->camera, PAN_STEP, 0);
	else if (keycode == XK_i)
		pan_camera(&scene->camera, 0, PAN_STEP);
	else if (keycode == XK_k)
		pan_camera(&scene->camera, 0, -PAN_STEP);
	else if (keycode == XK_r)
		scene->camera = scene->camera_init;
}

// adjust camera position and FOV
static void	adjust_camera(int keycode, t_scene *scene)
{
	if (keycode == XK_equal)
	{
		scene->camera.pos = vec3_add(scene->camera.pos,
				vec3_scale(scene->camera.dir, ZOOM_STEP));
		printf("Camera position: (%.1f, %.1f, %.1f)\n", scene->camera.pos.x,
			scene->camera.pos.y, scene->camera.pos.z);
	}
	else if (keycode == XK_minus)
	{
		scene->camera.pos = vec3_add(scene->camera.pos,
				vec3_scale(scene->camera.dir, -ZOOM_STEP));
		printf("Camera position: (%.1f, %.1f, %.1f)\n", scene->camera.pos.x,
			scene->camera.pos.y, scene->camera.pos.z);
	}
	else if (keycode == XK_1)
	{
		scene->camera.fov = fmax(1.0, scene->camera.fov - 5.0);
		scene->camera.half_w = tan(degrees_to_radians(scene->camera.fov / 2.0));
		printf("Camera FOV: %.1f degrees\n", scene->camera.fov);
	}
	else if (keycode == XK_2)
	{
		scene->camera.fov = fmin(180.0, scene->camera.fov + 5.0);
		scene->camera.half_w = tan(degrees_to_radians(scene->camera.fov / 2.0));
		printf("Camera FOV: %.1f degrees\n", scene->camera.fov);
	}
}

// Handle keyboard input: Escape quits, 'a' toggles debug axes, arrow keys
// rotate the camera, i/j/k/l pan it, 'r' resets to the initial camera.
// Any handled key triggers a re-render at the end.
int	key_hook(int keycode, void *param)
{
	t_scene	*scene;

	scene = (t_scene *)param;
	if (keycode == XK_Escape)
		close_window(scene);
	if (keycode == XK_a)
		scene->show_axes = !scene->show_axes;
	else if (keycode == XK_f)
		scene->show_fisheye = !scene->show_fisheye;
	else if (keycode == XK_equal || keycode == XK_minus || keycode == XK_1
		|| keycode == XK_2)
		adjust_camera(keycode, scene);
	else if (keycode == XK_Left || keycode == XK_Right
		|| keycode == XK_Up || keycode == XK_Down
		|| keycode == XK_j || keycode == XK_k
		|| keycode == XK_l || keycode == XK_i
		|| keycode == XK_r)
		handle_camera(keycode, scene);
	render_scene(scene);
	return (0);
}

// Re-render the scene whenever the window is exposed (e.g. uncovered)
int	expose_hook(void *data)
{
	render_scene((t_scene *)data);
	return (0);
}

// MLX main-loop hook; currently a no-op since rendering is event-driven
int	loop_hook(t_mlx *mlx)
{
	(void)mlx;
	return (0);
}
