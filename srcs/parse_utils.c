/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ka-tan <ka-tan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/24 15:15:07 by ka-tan            #+#    #+#             */
/*   Updated: 2026/05/24 19:43:10 by ka-tan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

// Count the number of tokens in a line (' ', '\n', '\t' delimiters)
static int	is_valid_double(const char *s)
{
	int	has_digit;

	has_digit = 0;
	if (*s == '-' || *s == '+')
		s++;
	while (*s == '.' || ft_isdigit(*s))
	{
		if (ft_isdigit(*s))
			has_digit = 1;
		s++;
	}
	if (*s != '\0' || !has_digit)
		return (0);
	return (1);
}

int	parse_double(const char *s, double *out)
{
	if (!s || is_valid_double(s))
		return (-1);
	*out = ft_atof(s);
	return (0);
}

/* Returns 1 if min <= value <= max, 0 otherwise. */
int	validate_range(double value, double min, double max)
{
	if (value >= min && value <= max)
		return (1);
	return (0);
}

int	parse_vec3(const char *token, t_vec3 *out)
{
	char	**parts;

	if (!token)
		return (-1);
	parts = ft_split(token, ',');
	if (!parts)
		return (-1);
	if (!parts[0] || !parts[1] || !parts[2] || parts[3])
	{
		free_tokens(parts);
		return (-1);
	}
	if (parse_double(parts[0], &out->x) == -1
		|| parse_double(parts[1], &out->y) == -1
		|| parse_double(parts[2], &out->z) == -1)
	{
		free_tokens(parts);
		return (-1);
	}
	free_tokens(parts);
	return (0);
}
