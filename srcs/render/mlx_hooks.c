#include "miniRT.h"

#define ROTATE_STEP_DEG 5.0
#define PAN_STEP 0.5

// Handle keyboard input: Escape quits, 'a' toggles debug axes, arrow keys
// rotate the camera, i/j/k/l pan it, 'r' resets to the initial camera.
// Any handled key triggers a re-render at the end.
int	key_hook(int keycode, void *param)
{
	t_scene	*scene;
	double	step;

	scene = (t_scene *)param;
	if (keycode == XK_Escape)
		close_window(scene);
	step = degrees_to_radians(ROTATE_STEP_DEG);
	if (keycode == XK_a)
		scene->show_axes = !scene->show_axes;
	else if (keycode == XK_Left)
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
	else
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
