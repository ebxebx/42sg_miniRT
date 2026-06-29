/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_shapes2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ka-tan <ka-tan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 23:21:57 by ka-tan            #+#    #+#             */
/*   Updated: 2026/05/31 19:06:31 by ka-tan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

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
