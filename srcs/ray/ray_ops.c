/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_ops.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zchoo <zchoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 20:43:45 by zchoo             #+#    #+#             */
/*   Updated: 2026/06/06 19:10:50 by zchoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "ray.h"
#include "vec3.h"

t_ray	ray_init(t_vec3 origin, t_vec3 direction)
{
	t_ray	r;

	r.origin = origin;
	r.direction = vec3_norm(direction);
	return (r);
}

// equivalent to (1 - t) * start + t * end
// start - (start * t) + (end * t)
// start + (end * t) - (start * t)
// start + (end - start) * t
// start + t * (end - start)

// start: the starting value
// end: the ending value
// t: the interpolation factor (0 <= t <= 1)
double lerp(double start, double end, double t)
{
    return (start + t * (end - start));
}

/* 
// origin
double hit_sphere(const t_vec3 center, double radius, const t_ray r) {
    t_vec3 oc = vec3_sub(r.origin, center);
    double a = vec3_dot(r.direction, r.direction);
    double b = 2.0 * vec3_dot(oc, r.direction);
    double c = vec3_dot(oc, oc) - radius*radius;
    double discriminant = b*b - 4*a*c;

    if (discriminant < 0)
        return -1.0;
	 else
        return ((-b - sqrt(discriminant)) / (2.0*a));
}
*/

// simplified version
double hit_sphere(const t_vec3 center, double radius, const t_ray r) {
    t_vec3 oc = vec3_sub(r.origin, center);
    double a = vec3_dot(r.direction, r.direction);
	double half_b = vec3_dot(oc, r.direction);
    double c = vec3_dot(oc, oc) - radius*radius;
	double discriminant = half_b*half_b - a*c;

    if (discriminant < 0)
        return -1.0;
	 else
        return ((-half_b - sqrt(discriminant)) / a);
}

t_vec3 ray_at(t_ray r, double t)
{
	return vec3_add(r.origin, vec3_scale(r.direction, t));
}

t_color	ray_color(t_ray r)
{
	double t = hit_sphere(vec3_init(0, 0, -1), 0.5, r);
    if (t > 0.0) {
        t_vec3 N = vec3_norm(vec3_sub(ray_at(r, t), vec3_init(0, 0, -1)));
        return (t_color){
			.r =  0.5 * (N.x + 1),
			.g =  0.5 * (N.y + 1),
			.b =  0.5 * (N.z + 1)
		};
    }
	
    t_vec3 unit_direction = vec3_norm(r.direction);
    double a = 0.5 * (unit_direction.y + 1.0);
	t_color col = {
		.r = lerp(1.0, 0.5, a),
		.g = lerp(1.0, 0.7, a),
		.b = lerp(1.0, 1.0, a)
	};
    return (col);
}
