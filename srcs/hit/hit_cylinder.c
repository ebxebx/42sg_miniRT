/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zchoo <zchoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 20:49:01 by zchoo             #+#    #+#             */
/*   Updated: 2026/07/15 23:11:12 by zchoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "quadratic.h"

// Given a candidate root from the infinite-tube equation, confirm it
// lands within the segment range AND within the cylinder's finite height
// (measured as the signed distance along the axis from the centre), then
// fill in the hit with a normal perpendicular to the axis.
static int	set_cylinder_side_hit(t_object *obj, t_ray_segment seg,
		double root, t_hit *hit)
{
	double	axis_pos;
	t_vec3	center_to_hit;

	if (root <= seg.t_min || root >= seg.t_max)
		return (0);
	hit->point = ray_at(seg.ray, root);
	center_to_hit = vec3_sub(hit->point, obj->shape.cy.centre);
	axis_pos = vec3_dot(center_to_hit, obj->shape.cy.axis);
	if (fabs(axis_pos) > obj->shape.cy.height / 2.0)
		return (0);
	hit->t = root;
	hit->normal = vec3_norm(vec3_sub(center_to_hit,
				vec3_scale(obj->shape.cy.axis, axis_pos)));
	hit->obj = obj;
	set_face_normal(seg.ray, hit);
	return (1);
}

// Ray-cylinder (infinite tube) intersection: project both the ray direction
// and the origin-to-centre vector onto the plane perpendicular to the
// cylinder's axis, then solve the resulting 2D ray-circle quadratic.
// Tries the nearer root first, falling back to the farther one.
static void	set_cylinder_side_quadratic(t_object *obj, t_ray_segment seg,
	t_quadratic *calc)
{
	t_vec3	oc;
	t_vec3	d_perp;
	t_vec3	oc_perp;

	oc = vec3_sub(seg.ray.origin, obj->shape.cy.centre);
	d_perp = vec3_sub(seg.ray.direction, vec3_scale(obj->shape.cy.axis,
				vec3_dot(seg.ray.direction, obj->shape.cy.axis)));
	oc_perp = vec3_sub(oc, vec3_scale(obj->shape.cy.axis,
				vec3_dot(oc, obj->shape.cy.axis)));
	calc->a = vec3_dot(d_perp, d_perp);
	calc->half_b = vec3_dot(d_perp, oc_perp);
	calc->c = vec3_dot(oc_perp, oc_perp)
		- obj->shape.cy.radius * obj->shape.cy.radius;
	calc->discriminant = calc->half_b * calc->half_b - calc->a * calc->c;
}

static int	hit_cylinder_side(t_object *obj, t_ray_segment seg, t_hit *hit)
{
	t_quadratic	quadratic;
	double		root;

	set_cylinder_side_quadratic(obj, seg, &quadratic);
	if (fabs(quadratic.a) < HIT_EPSILON || quadratic.discriminant < 0.0)
		return (0);
	root = (-quadratic.half_b - sqrt(quadratic.discriminant)) / quadratic.a;
	if (set_cylinder_side_hit(obj, seg, root, hit))
		return (1);
	root = (-quadratic.half_b + sqrt(quadratic.discriminant)) / quadratic.a;
	return (set_cylinder_side_hit(obj, seg, root, hit));
}

// Ray-disc intersection for one of the cylinder's flat end caps. offset is
// the signed distance from the cylinder centre to that cap along the axis
// (positive or negative half-height). Checks the ray hits the cap's plane
// within the segment range, then that the hit point falls inside the
// cap's radius. The cap normal points outward along the axis.
static int	test_cylinder_cap(t_object *obj, t_ray_segment seg,
		double offset, t_hit *hit)
{
	t_vec3	cap_center;
	double	denom;
	double	root;

	cap_center = vec3_add(obj->shape.cy.centre,
			vec3_scale(obj->shape.cy.axis, offset));
	denom = vec3_dot(seg.ray.direction, obj->shape.cy.axis);
	if (fabs(denom) < HIT_EPSILON)
		return (0);
	root = vec3_dot(vec3_sub(cap_center, seg.ray.origin),
			obj->shape.cy.axis) / denom;
	if (root <= seg.t_min || root >= seg.t_max)
		return (0);
	if (vec3_len(vec3_sub(ray_at(seg.ray, root), cap_center))
		> obj->shape.cy.radius)
		return (0);
	hit->t = root;
	hit->point = ray_at(seg.ray, root);
	hit->normal = obj->shape.cy.axis;
	if (offset < 0.0)
		hit->normal = vec3_neg(hit->normal);
	hit->obj = obj;
	set_face_normal(seg.ray, hit);
	return (1);
}

// Full cylinder intersection: test the round side and both end caps,
// shrinking seg.t_max after each hit so only the closest surface wins.
int	hit_cylinder_obj(t_object *obj, t_ray_segment seg, t_hit *hit)
{
	t_hit	temp;
	int		found;

	found = hit_cylinder_side(obj, seg, hit);
	if (found)
		seg.t_max = hit->t;
	if (test_cylinder_cap(obj, seg, obj->shape.cy.height / 2.0, &temp))
	{
		*hit = temp;
		found = 1;
		seg.t_max = hit->t;
	}
	if (test_cylinder_cap(obj, seg, -obj->shape.cy.height / 2.0, &temp))
	{
		*hit = temp;
		found = 1;
	}
	return (found);
}
