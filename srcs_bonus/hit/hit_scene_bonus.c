/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_scene_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zchoo <zchoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 20:49:08 by zchoo             #+#    #+#             */
/*   Updated: 2026/07/15 20:49:09 by zchoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

// Dispatch to the correct intersection routine based on the object's shape
static int	hit_object(t_object *obj, t_ray_segment seg, t_hit *hit)
{
	if (obj->type == SPHERE)
		return (hit_sphere_obj(obj, seg, hit));
	if (obj->type == PLANE)
		return (hit_plane_obj(obj, seg, hit));
	if (obj->type == CYLINDER)
		return (hit_cylinder_obj(obj, seg, hit));
	return (0);
}

// Walk every object in the scene, keeping only the closest hit by
// shrinking seg->t_max each time a nearer intersection is found
static int	hit_object_list(t_object *list, t_ray_segment *seg, t_hit *hit)
{
	t_object	*obj;
	t_hit		temp;
	int			found;

	found = 0;
	obj = list;
	while (obj)
	{
		if (hit_object(obj, *seg, &temp))
		{
			found = 1;
			seg->t_max = temp.t;
			*hit = temp;
		}
		obj = obj->next;
	}
	return (found);
}

// if the ray origin sits inside this axis's own (thin) radius, it would
// otherwise hit the inside wall point-blank and paint over the whole
// frame — skip the test for that ray instead.
static int	ray_inside_axis(t_object *axis, t_vec3 origin)
{
	t_vec3	oc;
	t_vec3	oc_perp;

	oc = vec3_sub(origin, axis->shape.cy.centre);
	oc_perp = vec3_sub(oc, vec3_scale(axis->shape.cy.axis,
				vec3_dot(oc, axis->shape.cy.axis)));
	return (vec3_len(oc_perp) < axis->shape.cy.radius);
}

// Same closest-hit walk as hit_object_list, but for the debug axes list,
// skipping any axis the ray origin is currently sitting inside of
static int	hit_axes(t_object *list, t_ray_segment *seg, t_hit *hit)
{
	t_object	*obj;
	t_hit		temp;
	int			found;

	found = 0;
	obj = list;
	while (obj)
	{
		if (!ray_inside_axis(obj, seg->ray.origin)
			&& hit_object(obj, *seg, &temp))
		{
			found = 1;
			seg->t_max = temp.t;
			*hit = temp;
		}
		obj = obj->next;
	}
	return (found);
}

// Find the closest intersection along ray within (HIT_EPSILON, t_max),
// checking scene objects first and then the debug axes if enabled
int	hit_scene(t_scene *scene, t_ray ray, double t_max, t_hit *hit)
{
	t_ray_segment	seg;
	int				found;

	seg.ray = ray;
	seg.t_min = HIT_EPSILON;
	seg.t_max = t_max;
	found = hit_object_list(scene->objects, &seg, hit);
	if (scene->show_axes)
		found |= hit_axes(scene->axes, &seg, hit);
	return (found);
}
