/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zchoo <zchoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 20:42:58 by zchoo             #+#    #+#             */
/*   Updated: 2026/06/01 20:44:59 by zchoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

# include <math.h>
# include "vec3.h"

typedef struct s_ray
{
	/* camera pos, or hit point for shadow rays */
	t_vec3			origin;

	/* MUST always be length 1.0 — normalise before storing */
	t_vec3			direction;
}					t_ray;
/* a point on the ray = origin + t * direction */

#endif