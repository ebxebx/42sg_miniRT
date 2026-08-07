/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wireframe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zchoo <zchoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/07 00:00:00 by zchoo             #+#    #+#             */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

#define WIREFRAME_SEGMENTS 32
#define WIREFRAME_GRID_SIZE 5
#define WIREFRAME_GRID_STEP 1.0

typedef struct s_screen_point
{
	int	x;
	int	y;
}t_screen_point;

static int	project_point(t_scene *scene, t_vec3 point, t_screen_point *out)
{
	t_vec3	rel;
	double	depth;

	rel = vec3_sub(point, scene->camera.pos);
	depth = vec3_dot(rel, scene->camera.dir);
	if (depth <= HIT_EPSILON)
		return (0);
	out->x = WIDTH / 2 + (int)(vec3_dot(rel, scene->camera.right) / depth
			* (WIDTH / 2) / scene->camera.half_w);
	out->y = HEIGHT / 2 - (int)(vec3_dot(rel, scene->camera.up) / depth
			* (WIDTH / 2) / scene->camera.half_w);
	return (1);
}

static void	put_wire_pixel(t_mlx *mlx, int x, int y, int colour)
{
	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
		my_mlx_pixel_put(mlx, x, y, colour);
}

static void	draw_line(t_mlx *mlx, t_screen_point a, t_screen_point b, int color)
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	int	e2;

	dx = abs(b.x - a.x);
	dy = -abs(b.y - a.y);
	sx = -1;
	sy = -1;
	if (a.x < b.x)
		sx = 1;
	if (a.y < b.y)
		sy = 1;
	err = dx + dy;
	while (1)
	{
		put_wire_pixel(mlx, a.x, a.y, color);
		if (a.x == b.x && a.y == b.y)
			break ;
		e2 = 2 * err;
		if (e2 >= dy)
			err += dy, a.x += sx;
		if (e2 <= dx)
			err += dx, a.y += sy;
	}
}

static void	draw_segment(t_scene *scene, t_vec3 start, t_vec3 end, int color)
{
	t_screen_point	a;
	t_screen_point	b;

	if (project_point(scene, start, &a) && project_point(scene, end, &b))
		draw_line(scene->mlx, a, b, color);
}

static t_vec3	perpendicular(t_vec3 axis)
{
	t_vec3	reference;

	reference = vec3_init(0, 1, 0);
	if (fabs(vec3_dot(axis, reference)) > 0.9)
		reference = vec3_init(1, 0, 0);
	return (vec3_norm(vec3_cross(axis, reference)));
}

static void	draw_circle(t_scene *scene, t_vec3 centre, t_vec3 axis,
	double radius, int color)
{
	t_vec3	u;
	t_vec3	v;
	t_vec3	previous;
	t_vec3	current;
	int		i;

	u = perpendicular(axis);
	v = vec3_cross(axis, u);
	previous = vec3_add(centre, vec3_scale(u, radius));
	i = 1;
	while (i <= WIREFRAME_SEGMENTS)
	{
		current = vec3_add(centre, vec3_add(vec3_scale(u, radius * cos(2
				* M_PI * i / WIREFRAME_SEGMENTS)), vec3_scale(v, radius * sin(2
				* M_PI * i / WIREFRAME_SEGMENTS))));
		draw_segment(scene, previous, current, color);
		previous = current;
		i++;
	}
}

static void	draw_sphere(t_scene *scene, t_sp sphere, int color)
{
	t_vec3	u;
	t_vec3	v;

	u = vec3_init(1, 0, 0);
	v = vec3_init(0, 1, 0);
	draw_circle(scene, sphere.centre, vec3_init(0, 0, 1), sphere.radius, color);
	draw_circle(scene, sphere.centre, u, sphere.radius, color);
	draw_circle(scene, sphere.centre, v, sphere.radius, color);
}

static void	draw_cylinder(t_scene *scene, t_cy cylinder, int color)
{
	t_vec3	top;
	t_vec3	bottom;
	t_vec3	u;
	t_vec3	v;

	top = vec3_add(cylinder.centre, vec3_scale(cylinder.axis,
			cylinder.height / 2));
	bottom = vec3_add(cylinder.centre, vec3_scale(cylinder.axis,
			-cylinder.height / 2));
	u = perpendicular(cylinder.axis);
	v = vec3_cross(cylinder.axis, u);
	draw_circle(scene, top, cylinder.axis, cylinder.radius, color);
	draw_circle(scene, bottom, cylinder.axis, cylinder.radius, color);
	draw_segment(scene, vec3_add(top, vec3_scale(u, cylinder.radius)),
		vec3_add(bottom, vec3_scale(u, cylinder.radius)), color);
	draw_segment(scene, vec3_sub(top, vec3_scale(u, cylinder.radius)),
		vec3_sub(bottom, vec3_scale(u, cylinder.radius)), color);
	draw_segment(scene, vec3_add(top, vec3_scale(v, cylinder.radius)),
		vec3_add(bottom, vec3_scale(v, cylinder.radius)), color);
	draw_segment(scene, vec3_sub(top, vec3_scale(v, cylinder.radius)),
		vec3_sub(bottom, vec3_scale(v, cylinder.radius)), color);
}

static void	draw_plane(t_scene *scene, t_pl plane, int color)
{
	t_vec3	u;
	t_vec3	v;
	int		i;

	u = perpendicular(plane.normal);
	v = vec3_cross(plane.normal, u);
	i = -WIREFRAME_GRID_SIZE;
	while (i <= WIREFRAME_GRID_SIZE)
	{
		draw_segment(scene, vec3_add(plane.point, vec3_add(vec3_scale(u, i
				* WIREFRAME_GRID_STEP), vec3_scale(v, -WIREFRAME_GRID_SIZE))),
			vec3_add(plane.point, vec3_add(vec3_scale(u, i * WIREFRAME_GRID_STEP),
			vec3_scale(v, WIREFRAME_GRID_SIZE))), color);
		draw_segment(scene, vec3_add(plane.point, vec3_add(vec3_scale(v, i
				* WIREFRAME_GRID_STEP), vec3_scale(u, -WIREFRAME_GRID_SIZE))),
			vec3_add(plane.point, vec3_add(vec3_scale(v, i * WIREFRAME_GRID_STEP),
			vec3_scale(u, WIREFRAME_GRID_SIZE))), color);
		i++;
	}
}

void	render_wireframe(t_scene *scene)
{
	t_object	*object;

	object = scene->objects;
	while (object)
	{
		if (object->type == SPHERE)
			draw_sphere(scene, object->shape.sp, pack_color(object->colour));
		else if (object->type == PLANE)
			draw_plane(scene, object->shape.pl, pack_color(object->colour));
		else
			draw_cylinder(scene, object->shape.cy, pack_color(object->colour));
		object = object->next;
	}
}
