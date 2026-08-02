/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_rotate_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zchoo <zchoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 21:48:54 by zchoo             #+#    #+#             */
/*   Updated: 2026/08/02 19:25:06 by zchoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

// Log the camera's current position and facing direction to stdout
static void	print_camera_info(t_camera *cam)
{
	printf("Camera position: (%f, %f, %f), direction: (%f, %f, %f)\n",
		cam->pos.x, cam->pos.y, cam->pos.z, cam->dir.x, cam->dir.y,
		cam->dir.z);
}

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
	print_camera_info(cam);
}

// Move the camera along its own right/up axes (screen-space panning),
// so the shift feels the same regardless of which way the camera faces.
void	pan_camera(t_camera *cam, double horizontal, double vertical)
{
	cam->pos = vec3_add(cam->pos, vec3_scale(cam->right, horizontal));
	cam->pos = vec3_add(cam->pos, vec3_scale(cam->up, vertical));
	print_camera_info(cam);
}

// Convert an angle in degrees to radians
double	degrees_to_radians(double degrees)
{
	return (degrees * M_PI / 180.0);
}

// Convert an angle in radians to degrees
double	radians_to_degrees(double radians)
{
	return (radians * 180.0 / M_PI);
}
