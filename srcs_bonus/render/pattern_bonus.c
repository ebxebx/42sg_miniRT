/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pattern_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zchoo <zchoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/05 00:00:00 by zchoo             #+#    #+#             */
/*   Updated: 2026/08/05 00:00:00 by zchoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

// Build a stable tangent along a plane, including for horizontal planes.
static t_vec3	plane_tangent(t_vec3 normal)
{
	t_vec3	reference;

	reference = vec3_init(0.0, 1.0, 0.0);
	if (fabs(vec3_dot(normal, reference)) > 0.99)
		reference = vec3_init(1.0, 0.0, 0.0);
	return (vec3_norm(vec3_cross(normal, reference)));
}

// Project onto the plane's local tangent axes. Ignoring the normal axis avoids
// floating-point flicker when the plane lies exactly on a cell boundary.
static long	plane_square(t_hit *hit)
{
	t_vec3	local;
	t_vec3	tangent;
	t_vec3	bitangent;
	long	square;

	local = vec3_sub(hit->point, hit->obj->shape.pl.point);
	tangent = plane_tangent(hit->obj->shape.pl.normal);
	bitangent = vec3_cross(hit->obj->shape.pl.normal, tangent);
	square = (long)floor(vec3_dot(local, tangent) / CHECKER_SIZE);
	square += (long)floor(vec3_dot(local, bitangent) / CHECKER_SIZE);
	return (square);
}

// Choose between an object's two colours. Planes use two local surface axes;
// curved objects retain the three-dimensional world-space pattern.
t_vec3	surface_colour(t_hit *hit)
{
	long	square;

	if (!hit->obj->is_checker)
		return (hit->obj->colour);
	if (hit->obj->type == PLANE)
		square = plane_square(hit);
	else
	{
		square = (long)floor(hit->point.x / CHECKER_SIZE);
		square += (long)floor(hit->point.y / CHECKER_SIZE);
		square += (long)floor(hit->point.z / CHECKER_SIZE);
	}
	if ((square % 2) == 0)
		return (hit->obj->colour);
	return (hit->obj->checker_colour);
}
