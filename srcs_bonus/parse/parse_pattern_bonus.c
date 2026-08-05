/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pattern_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zchoo <zchoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/05 00:00:00 by zchoo             #+#    #+#             */
/*   Updated: 2026/08/05 00:00:00 by zchoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

// An optional colour after the regular object colour enables checkerboard.
int	set_checker(t_object *obj, char *token)
{
	if (!token)
		return (0);
	if (parse_rgb(token, &obj->checker_colour) == -1)
		return (1);
	obj->is_checker = 1;
	return (0);
}
