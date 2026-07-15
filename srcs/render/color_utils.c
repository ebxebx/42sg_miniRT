/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zchoo <zchoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 19:41:03 by zchoo             #+#    #+#             */
/*   Updated: 2026/07/15 19:41:04 by zchoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

// Multiply two vectors component-wise (used to tint/combine colours,
// since colours are represented as vectors with components in [0, 1])
t_vec3	vec3_mul(t_vec3 a, t_vec3 b)
{
	return (vec3_init(a.x * b.x, a.y * b.y, a.z * b.z));
}

// Clamp each component of a colour vector into the valid [0, 1] range
t_vec3	vec3_clamp(t_vec3 v)
{
	if (v.x < 0.0)
		v.x = 0.0;
	if (v.y < 0.0)
		v.y = 0.0;
	if (v.z < 0.0)
		v.z = 0.0;
	if (v.x > 1.0)
		v.x = 1.0;
	if (v.y > 1.0)
		v.y = 1.0;
	if (v.z > 1.0)
		v.z = 1.0;
	return (v);
}

// Convert a clamped 0.0-1.0 RGB colour vector into a packed 0xRRGGBB int
// (0.999 nudges values like 1.0 to round down to 255 instead of 256)
int	pack_color(t_vec3 color)
{
	color = vec3_clamp(color);
	return (((int)(color.x * 255.999) << 16)
		| ((int)(color.y * 255.999) << 8)
		| (int)(color.z * 255.999));
}
