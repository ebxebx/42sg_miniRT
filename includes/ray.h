/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zchoo <zchoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 20:42:58 by zchoo             #+#    #+#             */
/*   Updated: 2026/06/07 13:52:38 by zchoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

# include "color.h"
# include "vec3.h"
# include <math.h>

typedef struct s_ray
{
	/* camera pos, or hit point for shadow rays */
	t_vec3	origin;

	/* MUST always be length 1.0 — normalise before storing */
	t_vec3	direction;
}			t_ray;
/* a point on the ray = origin + t * direction */

typedef struct s_ray_segment
{
	t_ray	ray;
	double	t_min;
	double	t_max;
}			t_ray_segment;

t_ray		ray_init(t_vec3 origin, t_vec3 direction);
t_vec3		ray_at(t_ray r, double t);
t_color		ray_color(t_ray r);

#endif
