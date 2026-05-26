/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zchoo <zchoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/24 16:34:35 by zchoo             #+#    #+#             */
/*   Updated: 2026/05/26 20:35:23 by zchoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC3_H
# define VEC3_H

# include <math.h>

# define EPSILON 1e-9

// 3D vector, can represent pos, dir, col, field of view(fov)
typedef struct s_vec3
{
	double	x;
	double	y;
	double	z;
}			t_vec3;

// vec3_ops.c
t_vec3		vec3_add(t_vec3 a, t_vec3 b);
t_vec3		vec3_sub(t_vec3 a, t_vec3 b);
t_vec3		vec3_scale(t_vec3 v, float s);
float		vec3_dot(t_vec3 a, t_vec3 b);
t_vec3		vec3_cross(t_vec3 a, t_vec3 b);

// vec3_ops2.c
t_vec3		vec3_norm(t_vec3 v);
float		vec3_len(t_vec3 v);
t_vec3		vec3_neg(t_vec3 v);

// vec3_helper.c
t_vec3		vec3_init(double x, double y, double z);
t_vec3		vec3_dup(t_vec3 v);
t_vec3		vec3_zero(void);
int			double_equal(double a, double b);

#endif