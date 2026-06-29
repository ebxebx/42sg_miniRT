/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ka-tan <ka-tan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/17 18:20:22 by ka-tan            #+#    #+#             */
/*   Updated: 2026/05/27 17:18:25 by ka-tan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "../libft/libft.h"
# include "../libft/get_next_line.h"
# include <errno.h>
# include <math.h>
# include "vec3.h"
# include "camera.h"

typedef struct s_scene	t_scene;
typedef struct s_object	t_object;

// parse_and_free_scene.c
int		parse_scene(const char *filename, t_scene *scene);
void	scene_free(t_scene *scene);

// parse_line.c (internal — used by parse_scene)
int		read_lines(int fd, t_scene *scene);

// parse_elements.c
int		check_scene_counts(t_scene *scene);
int		parse_ambient(char **tokens, t_scene *scene);
int		parse_camera(char **tokens, t_scene *scene);

// parse_light.c
int		parse_light(char **tokens, t_scene *scene);

// parse_shapes.c
int		dispatch_shape(char **tokens, t_scene *scene);
int		parse_sphere(char **tokens, t_scene *scene);
void	add_object(t_scene *scene, t_object *obj);

// parse_shapes2.c
int		parse_plane(char **tokens, t_scene *scene);
int		parse_cylinder(char **tokens, t_scene *scene);

// parse_utils_split.c
void	free_tokens(char **arr);
char	**split_line(const char *line);

// parse_utils.c
int		parse_double(const char *s, double *out);
int		validate_range(double value, double min, double max);
int		is_integer_value(double value);
int		parse_vec3(const char *token, t_vec3 *out);
int		parse_rgb(const char *token, t_vec3 *out);

#endif