/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ka-tan <ka-tan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 23:21:12 by ka-tan            #+#    #+#             */
/*   Updated: 2026/05/31 19:33:47 by ka-tan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

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

// Reads the file line by line, skipping blanks, stopping on the first error.
static int	read_lines(int fd, t_scene *scene)
{
	char	*line;
	int		failed;

	failed = 0;
	line = get_next_line(fd);
	while (line && !failed)
	{
		if (!is_blank_line(line))
			failed = process_line(line, scene);
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	return (failed);
}

// Opens the scene file, parses every line, and returns -1 on any error.
int	parse_scene(const char *filename, t_scene *scene)
{
	int	fd;
	int	failed;

	ft_bzero(scene, sizeof(t_scene));
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("Error: Cannot open scene file\n", 2);
		return (-1);
	}
	failed = read_lines(fd, scene);
	close(fd);
	if (failed)
		return (-1);
	if (check_scene_counts(scene))
		return (-1);
	return (0);
}
