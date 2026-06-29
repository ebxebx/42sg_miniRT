/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_ops.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zchoo <zchoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 20:43:45 by zchoo             #+#    #+#             */
/*   Updated: 2026/06/01 20:43:45 by zchoo            ###   ########.fr       */
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

t_vec3	ray_at(t_ray r, double t)
{
	return (vec3_add(r.origin, vec3_scale(r.direction, t)));
}
