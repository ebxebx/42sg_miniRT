/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ka-tan <ka-tan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 16:36:21 by zchoo             #+#    #+#             */
/*   Updated: 2026/03/28 20:47:28 by ka-tan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdint.h>

void	ft_lststrlcat(char *dest, t_list *head)
{
	t_list	*node;
	size_t	i;
	size_t	j;

	node = head;
	i = 0;
	while (node)
	{
		j = 0;
		while (((char *)node->content)[j] != '\0')
		{
			dest[i] = ((char *)node->content)[j];
			i++;
			j++;
		}
		node = node->next;
	}
	dest[i] = '\0';
}

size_t	get_total_bytes(t_list *head)
{
	size_t	total_bytes;
	size_t	i;
	t_list	*node;

	total_bytes = 0;
	node = head;
	while (node)
	{
		i = 0;
		while (((char *)node->content)[i++] != '\0')
			total_bytes++;
		node = node->next;
	}
	return (total_bytes);
}

// char	*ft_strndup(char *str, size_t n)
// {
// 	char	*copy;
// 	size_t	i;

// 	if (!str)
// 		return (NULL);
// 	copy = (char *)malloc(sizeof(char) * (n + 1));
// 	if (!copy)
// 		return (NULL);
// 	i = 0;
// 	while (i < n && str[i])
// 	{
// 		copy[i] = str[i];
// 		i++;
// 	}
// 	copy[i] = '\0';
// 	return (copy);
// }

void	*full_clean(char **leftover, t_list **lst, char **buf)
{
	if (buf && *buf)
	{
		free(*buf);
		*buf = NULL;
	}
	if (leftover && *leftover)
	{
		free(*leftover);
		*leftover = NULL;
	}
	if (lst && *lst)
		ft_lstclear(lst, free);
	return (NULL);
}
