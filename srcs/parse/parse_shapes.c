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

static int	parse_orient_token(const char *token, t_vec3 *dir, char *name)
{
	if (parse_vec3(token, dir) == -1)
	{
		ft_putstr_fd("Error: ", 2);
		ft_putstr_fd(name, 2);
		ft_putstr_fd(" orientation must be x,y,z\n", 2);
		return (1);
	}
	if (!validate_range(dir->x, -1.0, 1.0)
		|| !validate_range(dir->y, -1.0, 1.0)
		|| !validate_range(dir->z, -1.0, 1.0)
		|| double_equal(vec3_len(*dir), 0.0))
	{
		ft_putstr_fd("Error: ", 2);
		ft_putstr_fd(name, 2);
		ft_putstr_fd(" orientation components must be in [-1,1]", 2);
		ft_putendl_fd(" and not all zero", 2);
		return (1);
	}
	*dir = vec3_norm(*dir);
	return (0);
}

static t_object	*new_plane(t_vec3 point, t_vec3 normal, t_vec3 colour)
{
	t_object	*obj;

	obj = malloc(sizeof(t_object));
	if (!obj)
		return (NULL);
	obj->type = PLANE;
	obj->colour = colour;
	obj->shape.pl.point = point;
	obj->shape.pl.normal = normal;
	obj->next = NULL;
	return (obj);
}

static t_object	*new_cylinder(t_vec3 centre, t_vec3 axis, double *size,
		t_vec3 colour)
{
	t_object	*obj;

	obj = malloc(sizeof(t_object));
	if (!obj)
		return (NULL);
	obj->type = CYLINDER;
	obj->colour = colour;
	obj->shape.cy.centre = centre;
	obj->shape.cy.axis = axis;
	obj->shape.cy.radius = size[0] / 2.0;
	obj->shape.cy.height = size[1];
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

int	parse_plane(char **tokens, t_scene *scene)
{
	t_vec3		point;
	t_vec3		normal;
	t_vec3		colour;
	t_object	*obj;

	if (!tokens[1] || !tokens[2] || !tokens[3] || tokens[4])
	{
		ft_putstr_fd("Error: pl requires <point> <normal> <R,G,B>\n", 2);
		return (1);
	}
	if (parse_vec3(tokens[1], &point) == -1)
	{
		ft_putstr_fd("Error: Plane point must be x,y,z\n", 2);
		return (1);
	}
	if (parse_orient_token(tokens[2], &normal, "Plane") || parse_rgb(tokens[3],
			&colour) == -1)
		return (1);
	obj = new_plane(point, normal, colour);
	if (!obj)
		return (ft_putstr_fd("Error: malloc failed for plane\n", 2), 1);
	add_object(scene, obj);
	return (0);
}

int	parse_cylinder(char **tokens, t_scene *scene)
{
	t_vec3		centre;
	t_vec3		axis;
	t_vec3		colour;
	double		size[2];
	t_object	*obj;

	if (!tokens[1] || !tokens[2] || !tokens[3] || !tokens[4] || !tokens[5]
		|| tokens[6])
	{
		ft_putstr_fd("Error: cy requires <centre> <axis> <diameter>", 2);
		ft_putendl_fd(" <height> <R,G,B>", 2);
		return (1);
	}
	if (parse_vec3(tokens[1], &centre) == -1)
		return (ft_putstr_fd("Error: Cylinder centre must be x,y,z\n", 2), 1);
	if (parse_orient_token(tokens[2], &axis, "Cylinder"))
		return (1);
	if (parse_double(tokens[3], &size[0]) == -1 || size[0] <= 0.0
		|| parse_double(tokens[4], &size[1]) == -1 || size[1] <= 0.0)
		return (ft_putstr_fd("Error: Cylinder size must be positive\n", 2), 1);
	if (parse_rgb(tokens[5], &colour) == -1)
		return (1);
	obj = new_cylinder(centre, axis, size, colour);
	if (!obj)
		return (ft_putstr_fd("Error: malloc failed for cylinder\n", 2), 1);
	add_object(scene, obj);
	return (0);
}
