/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_rotate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zchoo <zchoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 21:48:54 by zchoo             #+#    #+#             */
/*   Updated: 2026/07/19 19:25:29 by zchoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

// Log the camera's current position and facing direction to stdout
static void	print_camera_info(t_camera *cam)
{
	printf("Camera position: (%f, %f, %f), direction: (%f, %f, %f)\n",
		cam->pos.x, cam->pos.y, cam->pos.z, cam->dir.x, cam->dir.y,
		cam->dir.z);
}

// Rotate around the camera's own axes.  Using world up for yaw degenerates
// when the camera looks straight up or down because dir is parallel to it.
// Rotating the whole local frame also keeps right/up continuous at the poles.
// Re-orthonormalise after each complete rotation to remove floating-point
// drift. Normalising each axis alone fixes its length, but not the small loss
// of perpendicularity between axes. Keep dir, rebuild right from dir/up, then
// rebuild up from the corrected right/dir so all three remain unit and square.
void	rotate_camera(t_camera *cam, double yaw, double pitch)
{
	cam->dir = vec3_rotate(cam->dir, cam->right, pitch);
	cam->up = vec3_rotate(cam->up, cam->right, pitch);
	cam->dir = vec3_rotate(cam->dir, cam->up, yaw);
	cam->right = vec3_rotate(cam->right, cam->up, yaw);
	cam->dir = vec3_norm(cam->dir);
	cam->right = vec3_norm(vec3_cross(cam->dir, cam->up));
	cam->up = vec3_norm(vec3_cross(cam->right, cam->dir));
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
