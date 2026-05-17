/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ka-tan <ka-tan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 16:36:25 by zchoo             #+#    #+#             */
/*   Updated: 2026/03/28 20:46:20 by ka-tan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 20
# endif

# include <stddef.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "libft.h"

char	*get_next_line(int fd);

void	ft_lststrlcat(char *dest, t_list *head);
size_t	get_total_bytes(t_list *head);
// char	*ft_strndup(char *str, size_t n);
void	*full_clean(char **leftover, t_list **lst, char **buf);

#endif