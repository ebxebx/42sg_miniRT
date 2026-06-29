/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zchoo <zchoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/17 19:06:18 by ka-tan            #+#    #+#             */
/*   Updated: 2026/06/06 18:24:14 by zchoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

#define HIT_EPSILON 0.001
#define ROTATE_STEP_DEG 5.0

static void	check_args(int argc, char **argv)
{
	char	*ext;

	if (argc < 2)
	{
		ft_putstr_fd("Error: Usage: ./miniRT <scene_file.rt>\n", 2);
		exit(1);
	}
	ext = ft_strrchr(argv[1], '.');
	if (!ext || ext == argv[1] || ext[-1] == '/' || ft_strcmp(ext, ".rt") != 0)
	{
		ft_putstr_fd("Error: Expected .rt file\n", 2);
		exit(1);
	}
}

static t_vec3	vec3_mul(t_vec3 a, t_vec3 b)
{
	return (vec3_init(a.x * b.x, a.y * b.y, a.z * b.z));
}

static t_vec3	vec3_clamp(t_vec3 v)
{
	if (v.x < 0.0)
		v.x = 0.0;
	if (v.y < 0.0)
		v.y = 0.0;
	if (v.z < 0.0)
		v.z = 0.0;
	if (v.x > 1.0)
		v.x = 1.0;
	if (v.y > 1.0)
		v.y = 1.0;
	if (v.z > 1.0)
		v.z = 1.0;
	return (v);
}

static int	pack_color(t_vec3 color)
{
	color = vec3_clamp(color);
	return (((int)(color.x * 255.999) << 16)
		| ((int)(color.y * 255.999) << 8)
		| (int)(color.z * 255.999));
}

static void	face_normal(t_ray ray, t_hit *hit)
{
	if (vec3_dot(ray.direction, hit->normal) > 0.0)
		hit->normal = vec3_neg(hit->normal);
}

static int	hit_sphere_obj(t_object *obj, t_ray_segment seg, t_hit *hit)
{
	t_vec3	oc;
	double	a;
	double	half_b;
	double	c;
	double	discriminant;
	double	root;

	oc = vec3_sub(seg.ray.origin, obj->shape.sp.centre);
	a = vec3_dot(seg.ray.direction, seg.ray.direction);
	half_b = vec3_dot(oc, seg.ray.direction);
	c = vec3_dot(oc, oc) - obj->shape.sp.radius * obj->shape.sp.radius;
	discriminant = half_b * half_b - a * c;
	if (discriminant < 0.0)
		return (0);
	root = (-half_b - sqrt(discriminant)) / a;
	if (root <= seg.t_min || root >= seg.t_max)
	{
		root = (-half_b + sqrt(discriminant)) / a;
		if (root <= seg.t_min || root >= seg.t_max)
			return (0);
	}
	hit->t = root;
	hit->point = ray_at(seg.ray, root);
	hit->normal = vec3_scale(vec3_sub(hit->point, obj->shape.sp.centre),
			1.0 / obj->shape.sp.radius);
	hit->obj = obj;
	face_normal(seg.ray, hit);
	return (1);
}

static int	hit_plane_obj(t_object *obj, t_ray_segment seg, t_hit *hit)
{
	double	denom;
	double	root;

	denom = vec3_dot(obj->shape.pl.normal, seg.ray.direction);
	if (fabs(denom) < HIT_EPSILON)
		return (0);
	root = vec3_dot(vec3_sub(obj->shape.pl.point, seg.ray.origin),
			obj->shape.pl.normal) / denom;
	if (root <= seg.t_min || root >= seg.t_max)
		return (0);
	hit->t = root;
	hit->point = ray_at(seg.ray, root);
	hit->normal = obj->shape.pl.normal;
	hit->obj = obj;
	face_normal(seg.ray, hit);
	return (1);
}

static int	set_cylinder_side_hit(t_object *obj, t_ray_segment seg, double root,
		t_hit *hit)
{
	double	axis_pos;
	t_vec3	center_to_hit;

	if (root <= seg.t_min || root >= seg.t_max)
		return (0);
	hit->point = ray_at(seg.ray, root);
	center_to_hit = vec3_sub(hit->point, obj->shape.cy.centre);
	axis_pos = vec3_dot(center_to_hit, obj->shape.cy.axis);
	if (fabs(axis_pos) > obj->shape.cy.height / 2.0)
		return (0);
	hit->t = root;
	hit->normal = vec3_norm(vec3_sub(center_to_hit,
				vec3_scale(obj->shape.cy.axis, axis_pos)));
	hit->obj = obj;
	face_normal(seg.ray, hit);
	return (1);
}

static int	hit_cylinder_side(t_object *obj, t_ray_segment seg, t_hit *hit)
{
	t_vec3	oc;
	t_vec3	d_perp;
	t_vec3	oc_perp;
	double	quad[3];
	double	discriminant;
	double	root;

	oc = vec3_sub(seg.ray.origin, obj->shape.cy.centre);
	d_perp = vec3_sub(seg.ray.direction, vec3_scale(obj->shape.cy.axis,
				vec3_dot(seg.ray.direction, obj->shape.cy.axis)));
	oc_perp = vec3_sub(oc, vec3_scale(obj->shape.cy.axis,
				vec3_dot(oc, obj->shape.cy.axis)));
	quad[0] = vec3_dot(d_perp, d_perp);
	quad[1] = vec3_dot(d_perp, oc_perp);
	quad[2] = vec3_dot(oc_perp, oc_perp)
		- obj->shape.cy.radius * obj->shape.cy.radius;
	discriminant = quad[1] * quad[1] - quad[0] * quad[2];
	if (fabs(quad[0]) < HIT_EPSILON || discriminant < 0.0)
		return (0);
	root = (-quad[1] - sqrt(discriminant)) / quad[0];
	if (set_cylinder_side_hit(obj, seg, root, hit))
		return (1);
	root = (-quad[1] + sqrt(discriminant)) / quad[0];
	return (set_cylinder_side_hit(obj, seg, root, hit));
}

static int	test_cylinder_cap(t_object *obj, t_ray_segment seg, double offset,
		t_hit *hit)
{
	t_vec3	cap_center;
	double	denom;
	double	root;

	cap_center = vec3_add(obj->shape.cy.centre,
			vec3_scale(obj->shape.cy.axis, offset));
	denom = vec3_dot(seg.ray.direction, obj->shape.cy.axis);
	if (fabs(denom) < HIT_EPSILON)
		return (0);
	root = vec3_dot(vec3_sub(cap_center, seg.ray.origin),
			obj->shape.cy.axis) / denom;
	if (root <= seg.t_min || root >= seg.t_max)
		return (0);
	if (vec3_len(vec3_sub(ray_at(seg.ray, root), cap_center))
		> obj->shape.cy.radius)
		return (0);
	hit->t = root;
	hit->point = ray_at(seg.ray, root);
	hit->normal = obj->shape.cy.axis;
	if (offset < 0.0)
		hit->normal = vec3_neg(hit->normal);
	hit->obj = obj;
	face_normal(seg.ray, hit);
	return (1);
}

static int	hit_cylinder_obj(t_object *obj, t_ray_segment seg, t_hit *hit)
{
	t_hit	temp;
	int		found;

	found = hit_cylinder_side(obj, seg, hit);
	if (found)
		seg.t_max = hit->t;
	if (test_cylinder_cap(obj, seg, obj->shape.cy.height / 2.0, &temp))
	{
		*hit = temp;
		found = 1;
		seg.t_max = hit->t;
	}
	if (test_cylinder_cap(obj, seg, -obj->shape.cy.height / 2.0, &temp))
	{
		*hit = temp;
		found = 1;
	}
	return (found);
}

static int	hit_object(t_object *obj, t_ray_segment seg, t_hit *hit)
{
	if (obj->type == SPHERE)
		return (hit_sphere_obj(obj, seg, hit));
	if (obj->type == PLANE)
		return (hit_plane_obj(obj, seg, hit));
	if (obj->type == CYLINDER)
		return (hit_cylinder_obj(obj, seg, hit));
	return (0);
}

static int	hit_object_list(t_object *list, t_ray_segment *seg, t_hit *hit)
{
	t_object	*obj;
	t_hit		temp;
	int			found;

	found = 0;
	obj = list;
	while (obj)
	{
		if (hit_object(obj, *seg, &temp))
		{
			found = 1;
			seg->t_max = temp.t;
			*hit = temp;
		}
		obj = obj->next;
	}
	return (found);
}

// if the ray origin sits inside this axis's own (thin) radius, it would
// otherwise hit the inside wall point-blank and paint over the whole
// frame — skip the test for that ray instead.
static int	ray_inside_axis(t_object *axis, t_vec3 origin)
{
	t_vec3	oc;
	t_vec3	oc_perp;

	oc = vec3_sub(origin, axis->shape.cy.centre);
	oc_perp = vec3_sub(oc, vec3_scale(axis->shape.cy.axis,
				vec3_dot(oc, axis->shape.cy.axis)));
	return (vec3_len(oc_perp) < axis->shape.cy.radius);
}

static int	hit_axes(t_object *list, t_ray_segment *seg, t_hit *hit)
{
	t_object	*obj;
	t_hit		temp;
	int			found;

	found = 0;
	obj = list;
	while (obj)
	{
		if (!ray_inside_axis(obj, seg->ray.origin)
			&& hit_object(obj, *seg, &temp))
		{
			found = 1;
			seg->t_max = temp.t;
			*hit = temp;
		}
		obj = obj->next;
	}
	return (found);
}

static int	hit_scene(t_scene *scene, t_ray ray, double t_max, t_hit *hit)
{
	t_ray_segment	seg;
	int				found;

	seg.ray = ray;
	seg.t_min = HIT_EPSILON;
	seg.t_max = t_max;
	found = hit_object_list(scene->objects, &seg, hit);
	if (scene->show_axes)
		found |= hit_axes(scene->axes, &seg, hit);
	return (found);
}

static t_ray	camera_ray(t_scene *scene, int x, int y)
{
	double	u;
	double	v;
	double	half_h;
	t_vec3	dir;

	half_h = scene->camera.half_w / ASPECT;
	u = ((x + 0.5) / (double)WIDTH * 2.0 - 1.0) * scene->camera.half_w;
	v = (1.0 - (y + 0.5) / (double)HEIGHT * 2.0) * half_h;
	dir = vec3_add(scene->camera.dir, vec3_add(vec3_scale(scene->camera.right,
					u), vec3_scale(scene->camera.up, v)));
	return (ray_init(scene->camera.pos, dir));
}

static int	in_shadow(t_scene *scene, t_hit *hit, t_light *light)
{
	t_vec3	to_light;
	double	dist;
	t_ray	shadow_ray;
	t_hit	shadow_hit;

	to_light = vec3_sub(light->pos, hit->point);
	dist = vec3_len(to_light);
	shadow_ray = ray_init(vec3_add(hit->point, vec3_scale(hit->normal,
					HIT_EPSILON)), to_light);
	return (hit_scene(scene, shadow_ray, dist, &shadow_hit));
}

static t_vec3	shade_hit(t_scene *scene, t_hit *hit)
{
	t_vec3	color;
	t_vec3	light_dir;
	t_vec3	diffuse;
	t_light	*light;
	double	intensity;

	color = vec3_scale(vec3_mul(hit->obj->colour, scene->ambient.colour),
			scene->ambient.ratio);
	light = scene->lights;
	while (light)
	{
		if (!in_shadow(scene, hit, light))
		{
			light_dir = vec3_norm(vec3_sub(light->pos, hit->point));
			intensity = vec3_dot(hit->normal, light_dir);
			if (intensity > 0.0)
			{
				diffuse = vec3_scale(vec3_mul(hit->obj->colour,
							light->colour), light->brightness * intensity);
				color = vec3_add(color, diffuse);
			}
		}
		light = light->next;
	}
	return (vec3_clamp(color));
}

void	render_scene(t_scene *scene)
{
	int		x;
	int		y;
	t_ray	ray;
	t_hit	hit;
	t_vec3	color;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			ray = camera_ray(scene, x, y);
			if (hit_scene(scene, ray, INFINITY, &hit))
				color = shade_hit(scene, &hit);
			else
				color = vec3_init(0.0, 0.0, 0.0);
			my_mlx_pixel_put(scene->mlx, x, y, pack_color(color));
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(scene->mlx->mlx, scene->mlx->win,
		scene->mlx->img, 0, 0);
}

int	init_mlx(t_mlx *mlx)
{
	mlx->mlx = mlx_init();
	if (!mlx->mlx)
		return (1);
	mlx->win = mlx_new_window(mlx->mlx, WIDTH, HEIGHT, "miniRT");
	if (!mlx->win)
		return (1);
	mlx->img = mlx_new_image(mlx->mlx, WIDTH, HEIGHT);
	if (!mlx->img)
		return (1);
	mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bpp, &mlx->line_len,
			&mlx->endian);
	if (!mlx->addr)
		return (1);
	return (0);
}

static int	free_memory(t_mlx *mlx)
{
	if (!mlx)
		return (1);
	free(mlx);
	return (0);
}

int	close_window(t_scene *scene)
{
	if (scene->mlx)
	{
		mlx_destroy_image(scene->mlx->mlx, scene->mlx->img);
		mlx_clear_window(scene->mlx->mlx, scene->mlx->win);
		mlx_destroy_window(scene->mlx->mlx, scene->mlx->win);
		mlx_destroy_display(scene->mlx->mlx);
		free_memory(scene->mlx);
		scene->mlx = NULL;
	}
	free_axes(scene->axes);
	scene_free(scene);
	exit(0);
	return (0);
}

int	key_hook(int keycode, void *param)
{
	t_scene	*scene;
	double	step;

	scene = (t_scene *)param;
	if (keycode == XK_Escape)
		close_window(scene);
	step = degrees_to_radians(ROTATE_STEP_DEG);
	if (keycode == XK_a)
		scene->show_axes = !scene->show_axes;
	else if (keycode == XK_Left)
		rotate_camera(&scene->camera, step, 0);
	else if (keycode == XK_Right)
		rotate_camera(&scene->camera, -step, 0);
	else if (keycode == XK_Up)
		rotate_camera(&scene->camera, 0, step);
	else if (keycode == XK_Down)
		rotate_camera(&scene->camera, 0, -step);
	else
		return (0);
	render_scene(scene);
	return (0);
}

int	expose_hook(void* data)
{
	render_scene((t_scene *)data);
	return (0);
}

int	loop_hook(t_mlx *mlx)
{
	(void)mlx;
	return (0);
}

int	main(int argc, char **argv)
{
	t_scene	scene;

	check_args(argc, argv);
	if (parse_scene(argv[1], &scene) == -1)
	{
		scene_free(&scene);
		return (1);
	}
	scene.mlx = malloc(sizeof(t_mlx));
	if (scene.mlx == NULL)
	{
		ft_putstr_fd("Error: Failed to allocate memory for mlx\n", 2);
		scene_free(&scene);
		return (1);
	}
	if (init_mlx(scene.mlx))
	{
		ft_putstr_fd("Error: Failed to initialize mlx\n", 2);
		free_memory(scene.mlx);
		scene.mlx = NULL;
		scene_free(&scene);
		return (1);
	}
	init_axes(&scene);
	mlx_key_hook(scene.mlx->win, key_hook, &scene);
	mlx_hook(scene.mlx->win, 17, 0, close_window, &scene);
	mlx_expose_hook(scene.mlx->win, expose_hook, &scene);
	mlx_loop_hook(scene.mlx->mlx, loop_hook, scene.mlx);
	render_scene(&scene);
	mlx_loop(scene.mlx->mlx);
	scene_free(&scene);
	return (0);
}
