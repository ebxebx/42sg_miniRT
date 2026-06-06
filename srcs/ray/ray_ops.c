/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_ops.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zchoo <zchoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 20:43:45 by zchoo             #+#    #+#             */
/*   Updated: 2026/06/06 18:55:44 by zchoo            ###   ########.fr       */
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

int hit_sphere(const t_vec3 center, double radius, const t_ray r) {
    t_vec3 oc = vec3_sub(r.origin, center);
    double a = vec3_dot(r.direction, r.direction);
    double b = 2.0 * vec3_dot(oc, r.direction);
    double c = vec3_dot(oc, oc) - radius*radius;
    double discriminant = b*b - 4*a*c;
    return (discriminant >= 0);
}

t_color	ray_color(t_ray r)
{
    if (hit_sphere(vec3_init(0, 0, -1.0), 0.5, r)) {
        return (t_color){1.0, 0, 0};
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
