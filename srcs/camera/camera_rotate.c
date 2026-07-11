#include "miniRT.h"

// pitch uses the camera's existing right axis (from the last frame) so it
// stays valid even if dir is currently near-vertical; yaw uses world up so
// the horizon stays level. build_camera_axes recomputes right/up/half_w
// afterwards, including its own near-vertical fallback.
void	rotate_camera(t_camera *cam, double yaw, double pitch)
{
	t_vec3	world_up;

	world_up = vec3_init(0, 1, 0);
	cam->dir = vec3_norm(vec3_rotate(cam->dir, cam->right, pitch));
	cam->dir = vec3_norm(vec3_rotate(cam->dir, world_up, yaw));
	build_camera_axes(cam);
}

double	degrees_to_radians(double degrees)
{
	return (degrees * M_PI / 180.0);
}

double	radians_to_degrees(double radians)
{
	return (radians * 180.0 / M_PI);
}
