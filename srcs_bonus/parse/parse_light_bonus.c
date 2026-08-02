/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zchoo <zchoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/31 21:07:29 by ka-tan            #+#    #+#             */
/*   Updated: 2026/07/15 20:22:21 by zchoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

// Validates the four tokens for an L line and fills pos, brightness, colour.
// Returns -1 and prints an error message if any field is invalid.
static int	parse_light_fields(char **t, t_vec3 *pos,
				double *brightness, t_vec3 *colour)
{
	if (!t[1] || !t[2] || !t[3] || t[4])
	{
		ft_putstr_fd("Error: L requires <pos x,y,z>", 2);
		ft_putendl_fd(" <brightness> <R,G,B>", 2);
		return (-1);
	}
	if (parse_vec3(t[1], pos) == -1)
	{
		ft_putstr_fd("Error: Light position must be x,y,z\n", 2);
		return (-1);
	}
	if (parse_double(t[2], brightness) == -1
		|| !validate_range(*brightness, 0.0, 1.0))
	{
		ft_putstr_fd("Error: Brightness must be between 0.0 and 1.0\n", 2);
		return (-1);
	}
	if (parse_rgb(t[3], colour) == -1)
		return (-1);
	return (0);
}

// Appends a new light node to the end of scene->lights.
static void	add_light(t_scene *scene, t_light *light)
{
	t_light	*last;

	if (!scene->lights)
	{
		scene->lights = light;
		return ;
	}
	last = scene->lights;
	while (last->next)
		last = last->next;
	last->next = light;
}

// Parses an L line: position vec3, brightness in [0,1], RGB colour.
// Allocates a t_light node and appends it to scene->lights.
int	parse_light(char **tokens, t_scene *scene)
{
	t_vec3	pos;
	double	brightness;
	t_vec3	colour;
	t_light	*light;

	if (parse_light_fields(tokens, &pos, &brightness, &colour) == -1)
		return (1);
	light = malloc(sizeof(t_light));
	if (!light)
	{
		ft_putstr_fd("Error: malloc failed for light\n", 2);
		return (1);
	}
	light->pos = pos;
	light->brightness = brightness;
	light->colour = colour;
	light->next = NULL;
	add_light(scene, light);
	return (0);
}
