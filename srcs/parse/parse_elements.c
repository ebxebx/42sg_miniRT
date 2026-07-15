/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zchoo <zchoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 23:21:57 by ka-tan            #+#    #+#             */
/*   Updated: 2026/07/15 20:22:05 by zchoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

// Checks A and C appeared exactly once, and L appeared at least once
// (several light sources are valid — their contributions are summed).
// Returns 1 and prints the specific error if not.
int	check_scene_counts(t_scene *scene)
{
	if (scene->has_ambient != 1)
	{
		if (scene->has_ambient == 0)
			ft_putstr_fd("Error: missing ambient (A)\n", 2);
		else
			ft_putstr_fd("Error: duplicate ambient (A)\n", 2);
		return (1);
	}
	if (scene->has_camera != 1)
	{
		if (scene->has_camera == 0)
			ft_putstr_fd("Error: missing camera (C)\n", 2);
		else
			ft_putstr_fd("Error: duplicate camera (C)\n", 2);
		return (1);
	}
	if (scene->has_light < 1)
	{
		ft_putstr_fd("Error: missing light (L)\n", 2);
		return (1);
	}
	return (0);
}

int	parse_ambient(char **tokens, t_scene *scene)
{
	if (tokens[1] == NULL || tokens[2] == NULL || tokens[3] != NULL)
	{
		ft_putstr_fd("Error: A requires <light intensity ratio>", 2);
		ft_putendl_fd(" and <colour in R,G,B>", 2);
		return (1);
	}
	if (parse_double(tokens[1], &scene->ambient.ratio) == -1
		|| !validate_range(scene->ambient.ratio, 0.0, 1.0))
	{
		ft_putstr_fd("Error: Ambient ratio must be between 0.0 and 1.0\n", 2);
		return (1);
	}
	if (parse_rgb(tokens[2], &scene->ambient.colour) == -1)
		return (1);
	return (0);
}

// Parses a "x,y,z" orientation token, validates each component in [-1.0, 1.0],
// then normalises to a unit vector so dot products in lighting are correct.
static int	parse_orient(const char *token, t_vec3 *dir)
{
	if (parse_vec3(token, dir) == -1)
	{
		ft_putstr_fd("Error: orientation must be in x,y,z format\n", 2);
		return (-1);
	}
	if (!validate_range(dir->x, -1.0, 1.0)
		|| !validate_range(dir->y, -1.0, 1.0)
		|| !validate_range(dir->z, -1.0, 1.0)
		|| double_equal(vec3_len(*dir), 0.0))
	{
		ft_putstr_fd("Error: orientation components must be in [-1.0, 1.0]", 2);
		ft_putendl_fd(" and not all zero", 2);
		return (-1);
	}
	*dir = vec3_norm(*dir);
	return (0);
}

// Derives the camera's right and up axes from its forward direction (dir), and
// precomputes half_w = tan(fov/2) so ray generation needs no trig per pixel.
// If dir is nearly parallel to world_up (0,1,0), the cross product degenerates
// to a zero vector — we fall back to (0,0,1) as the reference up axis instead.
// Note:
// camera pointing straight up or down — use z-axis as fallback
// tan(fov_deg/2 * pi/180) simplifies to tan(fov_deg * pi/360)
void	build_camera_axes(t_camera *cam)
{
	t_vec3	world_up;

	world_up.x = 0;
	world_up.y = 1;
	world_up.z = 0;
	if (fabs(vec3_dot(cam->dir, world_up)) > 0.99)
	{
		world_up.y = 0;
		world_up.z = 1;
	}
	cam->right = vec3_norm(vec3_cross(cam->dir, world_up));
	cam->up = vec3_cross(cam->right, cam->dir);
	cam->half_w = tan(cam->fov * M_PI / 360.0);
}

// Parses position (any real x,y,z), 
// orientation ([-1,1] per component, normalised),
// and FOV in degrees [0, 180].
// Derives camera axes after all fields are validated.
int	parse_camera(char **tokens, t_scene *scene)
{
	if (tokens[1] == NULL || tokens[2] == NULL
		|| tokens[3] == NULL || tokens[4] != NULL)
	{
		ft_putstr_fd("Error: C requires <pos x,y,z>", 2);
		ft_putendl_fd(" <orient x,y,z> <fov>", 2);
		return (1);
	}
	if (parse_vec3(tokens[1], &scene->camera.pos) == -1)
	{
		ft_putstr_fd("Error: Camera position must be x,y,z\n", 2);
		return (1);
	}
	if (parse_orient(tokens[2], &scene->camera.dir) == -1)
		return (1);
	if (parse_double(tokens[3], &scene->camera.fov) == -1
		|| !validate_range(scene->camera.fov, 0.0, 180.0)
		|| !is_integer_value(scene->camera.fov))
	{
		ft_putstr_fd("Error: FOV must be an integer between 0 and 180\n", 2);
		return (1);
	}
	build_camera_axes(&scene->camera);
	return (0);
}
