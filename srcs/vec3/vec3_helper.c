/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zchoo <zchoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/24 18:39:14 by zchoo             #+#    #+#             */
/*   Updated: 2026/05/24 22:06:42 by zchoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"

t_vec3	vec3_init(double x, double y, double z)
{
	return ((t_vec3){x, y, z});
}

t_vec3	vec3_dup(t_vec3 v)
{
	return (vec3_init(v.x, v.y, v.z));
}

t_vec3	vec3_zero(void)
{
	return (vec3_init(0.0f, 0.0f, 0.0f));
}
