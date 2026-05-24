/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils_split.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ka-tan <ka-tan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/24 15:15:07 by ka-tan            #+#    #+#             */
/*   Updated: 2026/05/24 21:47:13 by ka-tan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

// Count the number of tokens in a line (' ', '\n', '\t' delimiters)
static int count_tokens(const char *line)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	while(*line)
	{
		if (*line == ' ' || *line == '\n' || *line == '\t')
			in_word = 0;
		else if (!in_word)
		{
			in_word = 1;
			count++;
		}
		line++;
	}
	return (count);
}

//fills token with the split up values
static const char	*fill_tokens(char **tokens, const char *line, int i)
{
	const char	*start;

	while (*line == ' ' || *line == '\n' || *line == '\t')
		line++;
	if (!*line)
		return (line);
	start = line;
	while (*line && *line != ' ' && *line != '\n' && *line != '\t')
		line++;
	tokens[i] = ft_strndup(start, line - start);
	if (!tokens[i])
		return (NULL);
	return (line);
}

void	free_tokens(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

char	**split_line(const char *line)
{
	char		**tokens;
	int			count;
	int			i;

	count = count_tokens(line);
	tokens = malloc(sizeof(char *) * (count + 1));
	if (!tokens)
		return (NULL);
	i = 0;
	while (i <= count)
		tokens[i++] = NULL;
	i = 0;
	while (i < count)
	{
		line = fill_tokens(tokens, line, i);
		if (!line)
		{
			free_tokens(tokens);
			return (NULL);
		}
		i++;
	}
	tokens[i] = NULL;
	return (tokens);
}


