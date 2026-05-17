/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zchoo <zchoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 19:36:00 by zchoo             #+#    #+#             */
/*   Updated: 2025/11/27 14:26:20 by zchoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	int		total_size;
	char	*str_joined;

	total_size = ft_strlen(s1) + ft_strlen(s2);
	str_joined = malloc((total_size + 1) * sizeof(char));
	if (!str_joined)
		return (NULL);
	ft_strlcpy(str_joined, (char *)s1, ft_strlen(s1) + 1);
	ft_strlcpy(str_joined + ft_strlen(s1), (char *)s2, ft_strlen(s2) + 1);
	str_joined[total_size] = '\0';
	return (str_joined);
}
