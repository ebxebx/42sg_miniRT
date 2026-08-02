/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_ray_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zchoo <zchoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/02 20:06:30 by zchoo             #+#    #+#             */
/*   Updated: 2026/08/02 20:08:02 by zchoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

// Build the primary ray through pixel (x, y): map the pixel to normalised
// device coordinates (u, v) in [-1, 1] scaled by the camera's half-width/
// height, then offset the camera's forward direction by right*u + up*v
t_ray	camera_ray(t_scene *scene, int x, int y)
{
	double	u;
	double	v;
	double	half_h;
	t_vec3	dir;

	half_h = scene->camera.half_w / ASPECT;
	u = ((x + 0.5) / (double)WIDTH * 2.0 - 1.0) * scene->camera.half_w;
	v = (1.0 - (y + 0.5) / (double)HEIGHT * 2.0) * half_h;
	dir = vec3_add(scene->camera.dir, vec3_add(vec3_scale(scene->camera.right,
					u), vec3_scale(scene->camera.up, v)));
	return (ray_init(scene->camera.pos, dir));
}

t_ray	camera_ray_fisheye(t_scene *scene, int x, int y)
{
	t_camera		*cam;
	t_fisheye_math	fisheye;

	cam = &scene->camera;
	fisheye.radius = fmin(WIDTH, HEIGHT) / 2.0;
	fisheye.u = (x + 0.5 - WIDTH / 2.0) / fisheye.radius;
	fisheye.v = (HEIGHT / 2.0 - (y + 0.5)) / fisheye.radius;
	fisheye.r = sqrt(fisheye.u * fisheye.u + fisheye.v * fisheye.v);
	if (fisheye.r > 1.0)
		return (ray_init(cam->pos, vec3_zero()));
	if (fisheye.r < 1e-9)
		return (ray_init(cam->pos, cam->dir));
	fisheye.theta = fisheye.r * cam->fov * M_PI / 360.0;
	fisheye.radial = vec3_add(
			vec3_scale(cam->right, fisheye.u / fisheye.r),
			vec3_scale(cam->up, fisheye.v / fisheye.r));
	fisheye.dir = vec3_add(
			vec3_scale(cam->dir, cos(fisheye.theta)),
			vec3_scale(fisheye.radial, sin(fisheye.theta)));
	return (ray_init(cam->pos, fisheye.dir));
}
