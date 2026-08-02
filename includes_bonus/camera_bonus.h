/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zchoo <zchoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/02 18:17:57 by zchoo             #+#    #+#             */
/*   Updated: 2026/08/02 20:13:08 by zchoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_BONUS_H
# define CAMERA_BONUS_H

# include "vec3_bonus.h"
# include "ray_bonus.h"
# include "parse_bonus.h"

typedef struct s_fisheye_math
{
	double	radius;
	double	u;
	double	v;
	double	r;
	double	theta;
	t_vec3	radial;
	t_vec3	dir;
}	t_fisheye_math;

typedef struct s_camera	t_camera;

void	build_camera_axes(t_camera *cam);
void	rotate_camera(t_camera *cam, double yaw, double pitch);
void	pan_camera(t_camera *cam, double horizontal, double vertical);
double	degrees_to_radians(double degrees);
double	radians_to_degrees(double radians);
t_ray	camera_ray(t_scene *scene, int x, int y);
t_ray	camera_ray_fisheye(t_scene *scene, int x, int y);

#endif
