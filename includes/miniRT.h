/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ka-tan <ka-tan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/17 18:20:22 by ka-tan            #+#    #+#             */
/*   Updated: 2026/05/17 18:48:01 by ka-tan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "libft/libft.h"
# include <errno.h>

typedef struct	s_vec3
{
	double	x;
	double	y;
	double	z;
}	t_vec3;

typedef struct	s_ray
{
	t_vec3	origin;    /* camera pos, or hit point for shadow rays */
	t_vec3	direction; /* MUST always be length 1.0 — normalise before storing */
}	t_ray;
/* a point on the ray = origin + t * direction */

typedef struct	s_camera
{
	t_vec3	pos;
	t_vec3	dir;    /* forward, normalised */
	t_vec3	right;  /* cross(dir, world_up) — computed once at parse time */
	t_vec3	up;     /* cross(right, dir)    — computed once at parse time */
	double	fov;
	double	half_w; /* tan(fov/2) — precomputed, used in ray generation */
}	t_camera;

typedef enum	e_type
{
	SPHERE,
	PLANE,
	CYLINDER
}	t_type;

typedef struct s_sp
{
    t_vec3  centre;
    double  radius;
}   t_sp;

typedef struct s_pl
{
    t_vec3  point;
    t_vec3  normal;
}   t_pl;

typedef struct s_cy
{
    t_vec3  centre;
    t_vec3  axis;
    double  radius;
    double  height;
}   t_cy;

typedef union u_shape
{
    t_sp    sp;
    t_pl    pl;
    t_cy    cy;
}   t_shape;

typedef struct s_object
{
    int             type;
    t_vec3          colour;
    t_shape         shape;
    struct s_object *next;
}   t_object;

typedef struct	s_hit
{
	double		t;		/* distance — negative means no hit */
	t_vec3		point;	/* hit position: origin + t * direction */
	t_vec3		normal;	/* surface normal (always normalised) */
	t_object	*obj;	/* which object — needed for colour */
}				t_hit;

typedef struct	s_scene
{
	t_ambient	ambient;
	t_camera	camera;
	t_light		*lights;  /* linked list — bonus multi-lights works free */
	t_object	*objects; /* linked list of all shapes */
}	t_scene;

typedef struct	s_mlx
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_mlx;

#endif