/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_shapes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ka-tan <ka-tan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 23:21:57 by ka-tan            #+#    #+#             */
/*   Updated: 2026/05/31 19:06:31 by ka-tan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

// TODO: 6 functions currently (dispatch_shape, add_object, new_sphere, parse_sphere,
// new_plane, parse_plane) — norminette allows max 5 per file. Split before submission.

// Routes shape tokens (sp, pl, cy) to their parsers.
// Returns 0 on success, 1 with error message for unknown token.
int	dispatch_shape(char **tokens, t_scene *scene)
{
	if (ft_strcmp(tokens[0], "sp") == 0)
		return (parse_sphere(tokens, scene));
	if (ft_strcmp(tokens[0], "pl") == 0)
		return (parse_plane(tokens, scene));
	if (ft_strcmp(tokens[0], "cy") == 0)
		return (parse_cylinder(tokens, scene));
	ft_putstr_fd("Error: Unknown element '", 2);
	ft_putstr_fd(tokens[0], 2);
	ft_putstr_fd("'\n", 2);
	return (1);
}

// Appends obj to the end of scene->objects.
// Caller guarantees obj is non-NULL and already fully initialised.
void	add_object(t_scene *scene, t_object *obj)
{
	t_object	*last;

	if (!scene->objects)
	{
		scene->objects = obj;
		return ;
	}
	last = scene->objects;
	while (last->next)
		last = last->next;
	last->next = obj;
}

// Allocates and initialises a SPHERE object. Returns NULL on malloc failure.
static t_object	*new_sphere(t_vec3 centre, double diameter, t_vec3 colour)
{
	t_object	*obj;

	obj = malloc(sizeof(t_object));
	if (!obj)
		return (NULL);
	obj->type = SPHERE;
	obj->colour = colour;
	obj->shape.sp.centre = centre;
	obj->shape.sp.radius = diameter / 2.0;
	obj->next = NULL;
	return (obj);
}

// Parses: sp <centre x,y,z> <diameter> <R,G,B>
// Diameter must be positive; stored as radius = diameter / 2.
int	parse_sphere(char **tokens, t_scene *scene)
{
	t_vec3		centre;
	double		diameter;
	t_vec3		colour;
	t_object	*obj;

	if (!tokens[1] || !tokens[2] || !tokens[3] || tokens[4])
	{
		ft_putstr_fd("Error: sp requires <centre> <diameter> <R,G,B>\n", 2);
		return (1);
	}
	if (parse_vec3(tokens[1], &centre) == -1)
	{
		ft_putstr_fd("Error: Sphere centre must be x,y,z\n", 2);
		return (1);
	}
	if (parse_double(tokens[2], &diameter) == -1 || diameter <= 0.0)
	{
		ft_putstr_fd("Error: Sphere diameter must be positive\n", 2);
		return (1);
	}
	if (parse_rgb(tokens[3], &colour) == -1)
		return (1);
	obj = new_sphere(centre, diameter, colour);
	if (!obj)
	{
		ft_putstr_fd("Error: malloc failed for sphere\n", 2);
		return (1);
	}
	add_object(scene, obj);
	return (0);
}

/* TODO: implement */
int	parse_plane(char **tokens, t_scene *scene)
{
	(void)tokens;
	(void)scene;
	return (0);
}

/* TODO: implement */
int	parse_cylinder(char **tokens, t_scene *scene)
{
	(void)tokens;
	(void)scene;
	return (0);
}