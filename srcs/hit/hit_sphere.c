#include "miniRT.h"

void	face_normal(t_ray ray, t_hit *hit)
{
	if (vec3_dot(ray.direction, hit->normal) > 0.0)
		hit->normal = vec3_neg(hit->normal);
}

int	hit_sphere_obj(t_object *obj, t_ray_segment seg, t_hit *hit)
{
	t_vec3	oc;
	double	a;
	double	half_b;
	double	c;
	double	discriminant;
	double	root;

	oc = vec3_sub(seg.ray.origin, obj->shape.sp.centre);
	a = vec3_dot(seg.ray.direction, seg.ray.direction);
	half_b = vec3_dot(oc, seg.ray.direction);
	c = vec3_dot(oc, oc) - obj->shape.sp.radius * obj->shape.sp.radius;
	discriminant = half_b * half_b - a * c;
	if (discriminant < 0.0)
		return (0);
	root = (-half_b - sqrt(discriminant)) / a;
	if (root <= seg.t_min || root >= seg.t_max)
	{
		root = (-half_b + sqrt(discriminant)) / a;
		if (root <= seg.t_min || root >= seg.t_max)
			return (0);
	}
	hit->t = root;
	hit->point = ray_at(seg.ray, root);
	hit->normal = vec3_scale(vec3_sub(hit->point, obj->shape.sp.centre),
			1.0 / obj->shape.sp.radius);
	hit->obj = obj;
	face_normal(seg.ray, hit);
	return (1);
}
