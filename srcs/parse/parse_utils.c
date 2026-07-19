/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zchoo <zchoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/24 15:15:07 by ka-tan            #+#    #+#             */
/*   Updated: 2026/07/19 17:08:26 by zchoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

// Checks a string is a valid decimal number: an optional sign, digits,
// at most one '.', and nothing else trailing
static int	is_valid_double(const char *s)
{
	int	has_digit;
	int	has_dot;

	has_digit = 0;
	has_dot = 0;
	if (*s == '-' || *s == '+')
		s++;
	while (*s == '.' || ft_isdigit(*s))
	{
		if (*s == '.')
		{
			if (has_dot)
				return (0);
			has_dot = 1;
		}
		if (ft_isdigit(*s))
			has_digit = 1;
		s++;
	}
	if (*s != '\0' || !has_digit)
		return (0);
	return (1);
}

// Parses a string into a double, rejecting NULL, malformed numbers, and
// any trailing characters after the number. Returns -1 on failure.
int	parse_double(const char *s, double *out)
{
	char	*end;

	if (!s || !is_valid_double(s))
		return (-1);
	*out = strtod(s, &end);
	if (*end != '\0')
		return (-1);
	return (0);
}

// Parses a "x,y,z" token into a vec3, requiring exactly three
// comma-separated numeric parts. Returns -1 on any malformed input.
int	parse_vec3(const char *token, t_vec3 *out)
{
	char	**parts;

	if (!token)
		return (-1);
	parts = ft_split(token, ',');
	if (!parts || ft_chrcnt(token, ',') != 2)
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

// Parses an "R,G,B" token with each component in [0, 255], then
// normalises them to [0.0, 1.0] since colours are stored as unit vectors
int	parse_rgb(const char *token, t_vec3 *out)
{
	t_vec3	rgb;

	if (parse_vec3(token, &rgb) == -1)
	{
		ft_putstr_fd("Error: RGB must be three numbers in format R,G,B\n", 2);
		return (-1);
	}
	if (!validate_range(rgb.x, 0, 255) || !validate_range(rgb.y, 0, 255)
		|| !validate_range(rgb.z, 0, 255))
	{
		ft_putstr_fd("Error: RGB values must be between 0 and 255\n", 2);
		return (-1);
	}
	out->x = rgb.x / 255.0;
	out->y = rgb.y / 255.0;
	out->z = rgb.z / 255.0;
	return (0);
}
