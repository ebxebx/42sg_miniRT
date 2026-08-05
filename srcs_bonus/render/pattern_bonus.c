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

// Build one unit-length axis that lies on the plane's surface.
// The tangent must be perpendicular to the plane normal, so it is produced
// with a cross product against a reference direction. World-up is normally
// used as that reference. If the normal is almost parallel to world-up, the
// cross product would be nearly zero, so the X axis is used instead.
static t_vec3	plane_tangent(t_vec3 normal)
{
	t_vec3	reference;

	reference = vec3_init(0.0, 1.0, 0.0);
	if (fabs(vec3_dot(normal, reference)) > 0.99)
		reference = vec3_init(1.0, 0.0, 0.0);
	return (vec3_norm(vec3_cross(normal, reference)));
}

// Find the checker square containing a hit point on a plane.
// First move the hit into coordinates relative to the plane's anchor point.
// The tangent and bitangent form two perpendicular axes along the surface.
// Projecting the local hit onto them produces its surface coordinates. Each
// coordinate is divided by CHECKER_SIZE and floored to obtain a cell number;
// adding both numbers gives the parity used to alternate the two colours.
// The normal axis is ignored to avoid flicker near checker-cell boundaries.
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

// Return the material colour at the exact ray-hit position.
// A solid object immediately returns its primary colour. Checker planes use
// plane_square(), which keeps the grid attached to a rotated plane. Spheres
// and cylinders currently use a three-dimensional world-space grid: their
// X, Y, and Z cell numbers are added together. This is procedural mapping,
// not UV mapping, so the pattern does not wrap around curved surfaces.
// An even total selects the primary colour and an odd total selects the
// optional checker colour parsed from the scene file.
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
