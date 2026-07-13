/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_ops1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zchoo <zchoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/24 16:46:01 by zchoo             #+#    #+#             */
/*   Updated: 2026/05/24 17:10:40 by zchoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"

// Add two vectors component-wise
t_vec3	vec3_add(t_vec3 a, t_vec3 b)
{
	return ((t_vec3){a.x + b.x, a.y + b.y, a.z + b.z});
}

// Subtract vector b from vector a component-wise
t_vec3	vec3_sub(t_vec3 a, t_vec3 b)
{
	return ((t_vec3){a.x - b.x, a.y - b.y, a.z - b.z});
}

// Scale a vector by a scalar factor
t_vec3	vec3_scale(t_vec3 v, double s)
{
	return ((t_vec3){v.x * s, v.y * s, v.z * s});
}

// Compute the dot product of two vectors
// a . b = (a.x * b.x + a.y * b.y + a.z * b.z)
double	vec3_dot(t_vec3 a, t_vec3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

// Compute the cross product of two vectors
// a x b = (a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x)
t_vec3	vec3_cross(t_vec3 a, t_vec3 b)
{
	return ((t_vec3){a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y
		- a.y * b.x});
}
