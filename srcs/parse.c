/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zchoo <zchoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 23:21:12 by ka-tan            #+#    #+#             */
/*   Updated: 2026/05/26 20:26:30 by zchoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

//parse_scene, read_lines, open_scene, is_blank_line

// Returns 1 if line is blank or comment, 0 otherwise.
static int is_blank_line(const char *line)
{
	if(!line)
		return (1);
	while (*line == ' ' || *line == '\t')
		line++;
	if (*line == '#' || *line == '\0' || *line == '\n')
		return (1);
	return (0);
}

int	parse_scene(const char *filename, t_scene *scene)
{
	(void)filename;
	(void)scene;
	is_blank_line(NULL);
	return (0);
}

// static int open_scene 