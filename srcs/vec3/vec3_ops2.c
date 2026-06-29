/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_ops2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zchoo <zchoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/24 16:46:01 by zchoo             #+#    #+#             */
/*   Updated: 2026/05/26 20:40:36 by zchoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"

// Compute the normalised (unit) vector of a vector
//	||v|| = sqrt(v . v)
//	v̂ = v / ||v||
// If the length is zero, return a zero vector to avoid division by zero
t_vec3	vec3_norm(t_vec3 v)
{
	double	len;

	len = vec3_len(v);
	if (double_equal(len, 0.0))
		return (vec3_zero());
	return (vec3_scale(v, 1.0 / len));
}

// Compute the length (magnitude) of a vector
// ||v|| = sqrt(v . v)
double	vec3_len(t_vec3 v)
{
	return (sqrt(vec3_dot(v, v)));
}

// Compute the negation of a vector
// -v = (-v.x, -v.y, -v.z)
t_vec3	vec3_neg(t_vec3 v)
{
	return ((t_vec3){-v.x, -v.y, -v.z});
}

// Rotates v around a unit-length axis by angle (radians), Rodrigues' formula:
// v*cos(a) + (axis x v)*sin(a) + axis*(axis . v)*(1 - cos(a))
t_vec3	vec3_rotate(t_vec3 v, t_vec3 axis, double angle)
{
	t_vec3	spin;
	t_vec3	lean;

	spin = vec3_scale(vec3_cross(axis, v), sin(angle));
	lean = vec3_scale(axis, vec3_dot(axis, v) * (1.0 - cos(angle)));
	return (vec3_add(vec3_add(vec3_scale(v, cos(angle)), spin), lean));
}
