#include "miniRT.h"

// long thin cylinders standing in for axis lines — not real scene geometry.
// bump AXIS_RADIUS up for large-scale scenes, down for small ones.
#define AXIS_LENGTH 1000.0
#define AXIS_RADIUS 0.075

// Allocate one cylinder segment used to draw half of a debug axis
static t_object	*new_axis_seg(t_vec3 centre, t_vec3 axis, t_vec3 colour)
{
	t_object	*obj;

	obj = malloc(sizeof(t_object));
	if (!obj)
		return (NULL);
	obj->type = CYLINDER;
	obj->colour = colour;
	obj->shape.cy.centre = centre;
	obj->shape.cy.axis = axis;
	obj->shape.cy.radius = AXIS_RADIUS;
	obj->shape.cy.height = AXIS_LENGTH / 2.0;
	obj->next = NULL;
	return (obj);
}

// one half-length segment per direction so the brighter colour marks
// the positive end and the dim colour marks the negative end.
static t_object	*build_one_axis(t_vec3 dir, t_vec3 bright, t_vec3 dim)
{
	t_object	*pos;
	t_object	*neg;

	pos = new_axis_seg(vec3_scale(dir, AXIS_LENGTH / 4.0), dir, bright);
	neg = new_axis_seg(vec3_scale(dir, -AXIS_LENGTH / 4.0), dir, dim);
	if (!pos || !neg)
		return (NULL);
	pos->next = neg;
	return (pos);
}

// Build the red/green/blue X/Y/Z debug axes (6 cylinder segments total,
// chained via ->next) and store them on the scene; toggled by show_axes.
void	init_axes(t_scene *scene)
{
	t_object	*x_axis;
	t_object	*y_axis;
	t_object	*z_axis;

	scene->axes = NULL;
	scene->show_axes = 0;
	x_axis = build_one_axis(vec3_init(1, 0, 0), vec3_init(1, 0, 0),
			vec3_init(0.3, 0, 0));
	y_axis = build_one_axis(vec3_init(0, 1, 0), vec3_init(0, 1, 0),
			vec3_init(0, 0.3, 0));
	z_axis = build_one_axis(vec3_init(0, 0, 1), vec3_init(0, 0, 1),
			vec3_init(0, 0, 0.3));
	if (!x_axis || !y_axis || !z_axis)
		return ;
	x_axis->next->next = y_axis;
	y_axis->next->next = z_axis;
	scene->axes = x_axis;
}

// Free the linked list of debug-axis objects built by init_axes
void	free_axes(t_object *axes)
{
	t_object	*next;

	while (axes)
	{
		next = axes->next;
		free(axes);
		axes = next;
	}
}
