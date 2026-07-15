/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zchoo <zchoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 19:40:57 by zchoo             #+#    #+#             */
/*   Updated: 2026/07/15 20:02:44 by zchoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

#define ROTATE_STEP_DEG 5.0
#define PAN_STEP 0.5

static int	handle_camera(int keycode, t_scene *scene)
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
	return (0);
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
	else if (handle_camera(keycode, scene))
		return (0);
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
