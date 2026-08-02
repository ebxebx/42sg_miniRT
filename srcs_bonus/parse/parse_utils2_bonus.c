/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils2_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zchoo <zchoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 20:41:53 by zchoo             #+#    #+#             */
/*   Updated: 2026/07/15 20:44:06 by zchoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

/* Returns 1 if min <= value <= max, 0 otherwise. */
int	validate_range(double value, double min, double max)
{
	if (value >= min && value <= max)
		return (1);
	return (0);
}

// Returns 1 if value has no fractional part 
// e.g. FOV must be a whole number
int	is_integer_value(double value)
{
	return (value == (double)(long)value);
}
