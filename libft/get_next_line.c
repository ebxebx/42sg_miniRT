/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zchoo <zchoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 16:36:24 by zchoo             #+#    #+#             */
/*   Updated: 2025/12/12 10:32:32 by zchoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/types.h>
#include "get_next_line.h"

/*
	Function name		get_next_line
	Prototype 			char *get_next_line(int fd);
	Turn in files 		get_next_line.c, get_next_line_utils.c, get_next_line.h
	Parameters 			fd: The file descriptor to read from
	Return value 		Read line: correct behavior
						NULL: there is nothing else to read, or an error occurred
	External functs.	read, malloc, free
	Description 		Write a function that returns a line read from a file
						descriptor
*/

static char	*extract_line(t_list **head, ssize_t bytes_read, char **leftover,
	size_t nl)
{
	char	*line;
	size_t	total_bytes;

	if (bytes_read > 0 && nl < (size_t)bytes_read && *leftover == NULL)
		return (full_clean(leftover, head, NULL));
	line = NULL;
	if (bytes_read >= 0)
	{
		total_bytes = get_total_bytes(*head);
		if (total_bytes)
		{
			line = (char *)malloc(total_bytes + 1);
			if (line)
				ft_lststrlcat(line, *head);
		}
	}
	ft_lstclear(head, free);
	if (!line && leftover && *leftover)
	{
		free(*leftover);
		*leftover = NULL;
	}
	return (line);
}

static ssize_t	get_leftover_or_read(int fd, char **leftover,
	char **buf, size_t buffer_size)
{
	ssize_t	bytes_read;

	*buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!(*buf))
		return (-1);
	if (*leftover)
	{
		bytes_read = 0;
		while ((*leftover)[bytes_read]
			&& bytes_read < (ssize_t)buffer_size)
		{
			(*buf)[bytes_read] = (*leftover)[bytes_read];
			bytes_read++;
		}
		free(*leftover);
		*leftover = NULL;
	}
	else
		bytes_read = read(fd, *buf, buffer_size);
	return (bytes_read);
}

static size_t	find_newline(char *buf, size_t bytes_read)
{
	size_t	i;

	i = 0;
	while (i < bytes_read && buf[i] != '\n')
		i++;
	if (i < bytes_read && buf[i] == '\n')
		i++;
	return (i);
}

static int	add_chunk(t_list **lst, char *buf, size_t len)
{
	char	*chunk;
	t_list	*node;
	t_list	*new;

	chunk = ft_strndup(buf, len);
	if (!chunk)
		return (0);
	new = malloc(sizeof(t_list));
	if (!new)
		return (free(chunk), 0);
	new->content = chunk;
	new->next = NULL;
	node = *lst;
	if (!node)
		*lst = new;
	else
	{
		while (node && node->next)
			node = node->next;
		if (node)
			node->next = new;
	}
	return (1);
}

char	*get_next_line(int fd)
{
	static char	*leftover;
	char		*buf;
	ssize_t		bytes_read;
	t_list		*head;
	size_t		nl;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	head = NULL;
	bytes_read = get_leftover_or_read(fd, &leftover, &buf, BUFFER_SIZE);
	if (bytes_read <= 0)
		return (full_clean(&leftover, &head, &buf));
	while (bytes_read > 0)
	{
		buf[bytes_read] = '\0';
		nl = find_newline(buf, (size_t)bytes_read);
		if (!add_chunk(&head, buf, nl))
			return (full_clean(&leftover, &head, &buf));
		if (nl < (size_t)bytes_read)
			leftover = ft_strndup(&buf[nl], (size_t)bytes_read - nl);
		if (nl > 0 && buf[nl - 1] == '\n')
			break ;
		bytes_read = read(fd, buf, BUFFER_SIZE);
	}
	return (free(buf), extract_line(&head, bytes_read, &leftover, nl));
}
