/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zchoo <zchoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 10:36:38 by zchoo             #+#    #+#             */
/*   Updated: 2025/11/27 16:41:54 by zchoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char			*sub;
	size_t			copy;
	size_t			s_len;

	s_len = ft_strlen(s);
	if (start > s_len)
		copy = 0;
	else
	{
		copy = s_len - start;
		if (copy > len)
			copy = len;
	}
	sub = malloc((copy + 1) * sizeof(char));
	if (!sub)
		return (NULL);
	if (copy > 0)
		ft_strlcpy(sub, (char *)s + start, copy + 1);
	else
		sub[0] = 0;
	return (sub);
}
