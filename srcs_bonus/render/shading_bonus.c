/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shading_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zchoo <zchoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 20:08:03 by zchoo             #+#    #+#             */
/*   Updated: 2026/07/19 20:05:27 by zchoo            ###   ########.fr       */
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

// Cast a ray from the hit point towards the light and check whether
// anything blocks it before reaching the light. The origin is nudged
// along the normal by HIT_EPSILON to avoid the ray immediately
// re-hitting the same surface it started from ("shadow acne").
static int	in_shadow(t_scene *scene, t_hit *hit, t_light *light)
{
	t_vec3	to_light;
	double	dist;
	t_ray	shadow_ray;
	t_hit	shadow_hit;

	to_light = vec3_sub(light->pos, hit->point);
	dist = vec3_len(to_light);
	shadow_ray = ray_init(vec3_add(hit->point, vec3_scale(hit->normal,
					HIT_EPSILON)), to_light);
	return (hit_scene(scene, shadow_ray, dist, &shadow_hit));
}

// Compute the visible colour at a hit point: start from ambient light,
// then add each light's diffuse (Lambertian) contribution unless the
// point is in shadow from that light or facing away from it
t_vec3	shade_hit(t_scene *scene, t_hit *hit)
{
	t_vec3	color;
	t_vec3	light_dir;
	t_vec3	diffuse;
	t_light	*light;
	double	intensity;

	color = vec3_scale(vec3_mul(hit->obj->colour, scene->ambient.colour),
			scene->ambient.ratio);
	light = scene->lights;
	while (light)
	{
		if (!in_shadow(scene, hit, light))
		{
			light_dir = vec3_norm(vec3_sub(light->pos, hit->point));
			intensity = vec3_dot(hit->normal, light_dir);
			if (intensity > 0.0)
			{
				diffuse = vec3_scale(vec3_mul(hit->obj->colour,
							light->colour), light->brightness * intensity);
				color = vec3_add(color, diffuse);
			}
		}
		light = light->next;
	}
	return (vec3_clamp(color));
}
