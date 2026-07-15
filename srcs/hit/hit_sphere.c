/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_sphere.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zchoo <zchoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 20:49:11 by zchoo             #+#    #+#             */
/*   Updated: 2026/07/15 22:08:49 by zchoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "quadratic.h"

// Flip the hit normal so it always points back towards the ray origin,
// i.e. against the incoming ray direction (needed for correct shading
// whether the ray hits the outside or the inside of a surface)
void	face_normal(t_ray ray, t_hit *hit)
{
	if (vec3_dot(ray.direction, hit->normal) > 0.0)
		hit->normal = vec3_neg(hit->normal);
}

static void	set_sphere_quadratic(t_object *obj, t_ray_segment seg,
	t_quadratic *calc)
{
	t_vec3	oc;

	oc = vec3_sub(seg.ray.origin, obj->shape.sp.centre);
	calc->a = vec3_dot(seg.ray.direction, seg.ray.direction);
	calc->half_b = vec3_dot(oc, seg.ray.direction);
	calc->c = vec3_dot(oc, oc) - obj->shape.sp.radius * obj->shape.sp.radius;
	calc->discriminant = calc->half_b * calc->half_b - calc->a * calc->c;
}

// Ray-sphere intersection via the quadratic formula:
// |origin + t*dir - centre|^2 = radius^2 expands to a*t^2 + 2*half_b*t + c = 0.
// Tries the nearer root first, then the farther one, keeping whichever
// lands within the segment's [t_min, t_max] range.
int	hit_sphere_obj(t_object *obj, t_ray_segment seg, t_hit *hit)
{
	t_quadratic	quadratic;
	double		root;

	set_sphere_quadratic(obj, seg, &quadratic);
	if (quadratic.discriminant < 0.0)
		return (0);
	root = (-quadratic.half_b - sqrt(quadratic.discriminant))
		/ quadratic.a;
	if (root <= seg.t_min || root >= seg.t_max)
	{
		root = (-quadratic.half_b + sqrt(quadratic.discriminant))
			/ quadratic.a;
		if (root <= seg.t_min || root >= seg.t_max)
			return (0);
	}
	hit->t = root;
	hit->point = ray_at(seg.ray, root);
	hit->normal = vec3_scale(vec3_sub(hit->point, obj->shape.sp.centre), 1.0
			/ obj->shape.sp.radius);
	hit->obj = obj;
	face_normal(seg.ray, hit);
	return (1);
}
