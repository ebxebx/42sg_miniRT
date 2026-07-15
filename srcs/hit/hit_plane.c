/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_plane.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zchoo <zchoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 20:49:05 by zchoo             #+#    #+#             */
/*   Updated: 2026/07/15 23:11:12 by zchoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

// Ray-plane intersection: solve (origin + t*dir - point) . normal = 0 for t.
// If the ray direction is (near) parallel to the plane, denom is ~0 and
// there is no single intersection point, so bail out early.
int	hit_plane_obj(t_object *obj, t_ray_segment seg, t_hit *hit)
{
	double	denom;
	double	root;

	denom = vec3_dot(obj->shape.pl.normal, seg.ray.direction);
	if (fabs(denom) < HIT_EPSILON)
		return (0);
	root = vec3_dot(vec3_sub(obj->shape.pl.point, seg.ray.origin),
			obj->shape.pl.normal) / denom;
	if (root <= seg.t_min || root >= seg.t_max)
		return (0);
	hit->t = root;
	hit->point = ray_at(seg.ray, root);
	hit->normal = obj->shape.pl.normal;
	hit->obj = obj;
	set_face_normal(seg.ray, hit);
	return (1);
}
