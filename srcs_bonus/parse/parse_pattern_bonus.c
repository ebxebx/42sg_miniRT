/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pattern_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zchoo <zchoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/05 18:23:37 by zchoo             #+#    #+#             */
/*   Updated: 2026/08/05 19:15:56 by zchoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

// Require tokens 1..required, allow one optional checker colour, and reject
// anything after it without reading beyond the NULL-terminated token array.
int	invalid_shape_tokens(char **tokens, int required)
{
	int	i;

	i = 1;
	while (i <= required)
	{
		if (!tokens[i])
			return (1);
		i++;
	}
	if (tokens[required + 1] && tokens[required + 2])
		return (1);
	return (0);
}

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
