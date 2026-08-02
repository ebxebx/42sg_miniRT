/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shading_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zchoo <zchoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 20:08:03 by zchoo             #+#    #+#             */
/*   Updated: 2026/08/02 20:15:03 by zchoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

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

// Compute the specular highlight color at a hit point
// The reflection vector is:
// R = 2 × N × dot(N, L) − L
// The view direction must point from the hit point toward the camera:
// V = normalize(camera_position − hit_position)
// Then:
// specular = pow(max(dot(R, V), 0), shininess)
static t_vec3	specular_colour(t_scene *scene, t_hit *hit,
		t_light *light, t_vec3 light_dir)
{
	t_vec3	view_dir;
	t_vec3	reflected;
	double	factor;
	double	normal_dot_light;

	normal_dot_light = vec3_dot(hit->normal, light_dir);
	reflected = vec3_sub(vec3_scale(hit->normal,
				2.0 * normal_dot_light), light_dir);
	view_dir = vec3_norm(vec3_sub(scene->camera.pos, hit->point));
	factor = fmax(vec3_dot(reflected, view_dir), 0.0);
	factor = pow(factor, SHININESS);
	factor *= light->brightness * SPECULAR_STRENGTH;
	return (vec3_scale(light->colour, factor));
}

// Return one visible light's diffuse and specular contribution.
// A light behind the surface contributes no colour.
static t_vec3	light_contribution(t_scene *scene, t_hit *hit, t_light *light)
{
	t_vec3	light_dir;
	t_vec3	diffuse;
	t_vec3	specular;
	double	intensity;

	light_dir = vec3_norm(vec3_sub(light->pos, hit->point));
	intensity = vec3_dot(hit->normal, light_dir);
	if (intensity <= 0.0)
		return (vec3_zero());
	diffuse = vec3_scale(vec3_mul(hit->obj->colour, light->colour),
			light->brightness * intensity);
	specular = specular_colour(scene, hit, light, light_dir);
	return (vec3_add(diffuse, specular));
}

// Start with ambient colour, then accumulate every unblocked light's
// diffuse and specular contribution before clamping the final result.
t_vec3	shade_hit(t_scene *scene, t_hit *hit)
{
	t_vec3	color;
	t_light	*light;

	color = vec3_scale(vec3_mul(hit->obj->colour, scene->ambient.colour),
			scene->ambient.ratio);
	light = scene->lights;
	while (light)
	{
		if (!in_shadow(scene, hit, light))
			color = vec3_add(color, light_contribution(scene, hit, light));
		light = light->next;
	}
	return (vec3_clamp(color));
}
