#include "miniRT.h"

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
	face_normal(seg.ray, hit);
	return (1);
}
