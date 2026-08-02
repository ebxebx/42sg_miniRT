/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zchoo <zchoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/17 18:20:22 by ka-tan            #+#    #+#             */
/*   Updated: 2026/07/19 19:25:59 by zchoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_BONUS_H
# define MINIRT_BONUS_H

# include "../libft/get_next_line.h"
# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include "mlx_helper_bonus.h"
# include "parse_bonus.h"
# include "axes_bonus.h"
# include "camera_bonus.h"
# include "ray_bonus.h"
# include "vec3_bonus.h"
# include "render_bonus.h"
# include <X11/Xlib.h>
# include <X11/keysym.h>
# include <errno.h>
# include <math.h>
# include <stdio.h>

// # define WIDTH 480
// # define HEIGHT 270
# define WIDTH 720
# define HEIGHT 405
// # define ASPECT ((double)WIDTH / HEIGHT) // NORMINATE NOT ALLOW
# define ASPECT 1.77778
# define FOV_MAX 180

/* ------------------------------------------------------------------ */
/*  SCENE ELEMENTS                                                    */
/* ------------------------------------------------------------------ */

typedef struct s_ambient
{
	double			ratio;
	t_vec3			colour;
}					t_ambient;

typedef struct s_light
{
	t_vec3			pos;
	double			brightness;
	t_vec3			colour;
	struct s_light	*next;
}					t_light;

typedef struct s_camera
{
	t_vec3			pos;

	/* forward, normalised */
	t_vec3			dir;

	/* cross(dir, world_up) — computed once at parse time */
	t_vec3			right;

	/* cross(right, dir)    — computed once at parse time */
	t_vec3			up;
	double			fov;

	/* tan(fov/2) — precomputed, used in ray generation */
	double			half_w;
}					t_camera;

typedef enum e_type
{
	SPHERE,
	PLANE,
	CYLINDER
}					t_type;

typedef struct s_sp
{
	t_vec3			centre;
	double			radius;
}					t_sp;

typedef struct s_pl
{
	t_vec3			point;
	t_vec3			normal;
}					t_pl;

typedef struct s_cy
{
	t_vec3			centre;
	t_vec3			axis;
	double			radius;
	double			height;
}					t_cy;

typedef union u_shape
{
	t_sp			sp;
	t_pl			pl;
	t_cy			cy;
}					t_shape;

typedef struct s_object
{
	t_type			type;
	t_vec3			colour;
	t_shape			shape;
	struct s_object	*next;
}					t_object;

typedef struct s_hit
{
	/* distance — negative means no hit */
	double			t;

	/* hit position: origin + t * direction */
	t_vec3			point;

	/* surface normal (always normalised) */
	t_vec3			normal;

	/* which object — needed for colour */
	t_object		*obj;
}					t_hit;

typedef struct s_scene
{
	/* flags to check for duplicates */
	int				has_ambient;
	int				has_camera;
	int				has_light;

	t_ambient		ambient;
	t_camera		camera;

	/* snapshot of camera as parsed — restored by the 'R' reset hook */
	t_camera		camera_init;

	/* linked list — bonus multi-lights works free */
	t_light			*lights;

	/* linked list of all shapes */
	t_object		*objects;

	/* debug overlay — X/Y/Z axis lines, toggled with the 'A' key */
	t_object		*axes;
	int				show_axes;

	/* debug overlay — fisheye effect, toggled with the 'F' key */
	int				show_fisheye;

	t_mlx			*mlx;
}					t_scene;

#endif
