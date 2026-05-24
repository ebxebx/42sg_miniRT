/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_ops2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zchoo <zchoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/24 16:46:01 by zchoo             #+#    #+#             */
/*   Updated: 2026/05/24 18:21:13 by zchoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"

// Compute the normalised (unit) vector of a vector
//	||v|| = sqrt(v . v)
//	v̂ = v / ||v||
t_vec3	vec3_norm(t_vec3 v)
{
	float len = vec3_len(v);
	return (vec3_scale(v, 1.0f / len));
}

// Compute the length (magnitude) of a vector
// ||v|| = sqrt(v . v)
float	vec3_len(t_vec3 v)
{
	return (sqrtf(vec3_dot(v, v)));
}

// Compute the negation of a vector
// -v = (-v.x, -v.y, -v.z)
t_vec3	vec3_neg(t_vec3 v)
{
	return ((t_vec3){-v.x, -v.y, -v.z});
}
