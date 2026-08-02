/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_helper_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zchoo <zchoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/24 18:39:14 by zchoo             #+#    #+#             */
/*   Updated: 2026/07/19 19:58:16 by zchoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3_bonus.h"

// Build a vector from its three components
t_vec3	vec3_init(double x, double y, double z)
{
	return ((t_vec3){x, y, z});
}

// Return a copy of a vector
t_vec3	vec3_dup(t_vec3 v)
{
	return (vec3_init(v.x, v.y, v.z));
}

// Return the zero vector (0, 0, 0)
t_vec3	vec3_zero(void)
{
	return (vec3_init(0.0, 0.0, 0.0));
}

// Check if two vectors are equal
int	vec3_equal(t_vec3 a, t_vec3 b)
{
	return (double_equal(a.x, b.x)
		&& double_equal(a.y, b.y) && double_equal(a.z, b.z));
}

// Check if two doubles are approximately equal
int	double_equal(double a, double b)
{
	return (fabs(a - b) < EPSILON);
}
