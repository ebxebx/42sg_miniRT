/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zchoo <zchoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 23:21:12 by ka-tan            #+#    #+#             */
/*   Updated: 2026/07/15 23:35:20 by zchoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

// Returns 1 if the line is empty, whitespace-only, or starts with '#'.
static int	is_blank_line(const char *line)
{
	if (!line)
		return (1);
	while (*line == ' ' || *line == '\t')
		line++;
	if (*line == '#' || *line == '\0' || *line == '\n')
		return (1);
	return (0);
}

// Routes a tokenised line to the correct parser based on the element type.
static int	dispatch_line(char **tokens, t_scene *scene)
{
	if (ft_strcmp(tokens[0], "A") == 0)
	{
		scene->has_ambient++;
		return (parse_ambient(tokens, scene));
	}
	if (ft_strcmp(tokens[0], "C") == 0)
	{
		scene->has_camera++;
		return (parse_camera(tokens, scene));
	}
	if (ft_strcmp(tokens[0], "L") == 0)
	{
		scene->has_light++;
		return (parse_light(tokens, scene));
	}
	return (dispatch_shape(tokens, scene));
}

// Splits a raw line into tokens, dispatches it, then frees the tokens.
static int	process_line(char *line, t_scene *scene)
{
	char	**tokens;
	int		failed;

	tokens = split_line(line);
	if (!tokens)
		return (-1);
	failed = dispatch_line(tokens, scene);
	free_tokens(tokens);
	return (failed);
}

// Reads the file line by line, skipping blanks, stopping process on the first
// error, but reads the entire file to free all lines.
// Returns 1 on any error, else 0.
int	read_lines(int fd, t_scene *scene)
{
	char	*line;
	int		failed;

	failed = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (!failed && !is_blank_line(line))
			failed = process_line(line, scene);
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	return (failed);
}
