#ifndef RENDER_H
# define RENDER_H

# include "parse.h"
# include "ray.h"
# include "vec3.h"
# include "mlx_helper.h"

typedef struct s_hit	t_hit;

# define HIT_EPSILON 0.001

// color_utils.c
t_vec3	vec3_mul(t_vec3 a, t_vec3 b);
t_vec3	vec3_clamp(t_vec3 v);
int		pack_color(t_vec3 color);

// hit_sphere.c
void	set_face_normal(t_ray ray, t_hit *hit);
int		hit_sphere_obj(t_object *obj, t_ray_segment seg, t_hit *hit);

// hit_plane.c
int		hit_plane_obj(t_object *obj, t_ray_segment seg, t_hit *hit);

// hit_cylinder.c
int		hit_cylinder_obj(t_object *obj, t_ray_segment seg, t_hit *hit);

// hit_scene.c
int		hit_scene(t_scene *scene, t_ray ray, double t_max, t_hit *hit);

// shading.c
t_ray	camera_ray(t_scene *scene, int x, int y);
t_ray	camera_ray_fisheye(t_scene *scene, int x, int y);
t_vec3	shade_hit(t_scene *scene, t_hit *hit);

// render.c
void	render_scene(t_scene *scene);
int		init_mlx(t_mlx *mlx);
int		close_window(t_scene *scene);

// mlx_hooks.c
int		key_hook(int keycode, void *param);
int		expose_hook(void *data);
int		loop_hook(t_mlx *mlx);

#endif
