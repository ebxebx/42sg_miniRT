/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zchoo <zchoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 16:19:11 by zchoo             #+#    #+#             */
/*   Updated: 2025/11/27 13:43:17 by zchoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*s1_b;
	unsigned char	*s2_b;

	i = 0;
	s1_b = (unsigned char *)s1;
	s2_b = (unsigned char *)s2;
	while (i < n && *s1_b && *s2_b)
	{
		if (*s1_b != *s2_b)
			return (*s1_b - *s2_b);
		s1_b++;
		s2_b++;
		i++;
	}
	if (i < n)
		return (*s1_b - *s2_b);
	return (0);
}
