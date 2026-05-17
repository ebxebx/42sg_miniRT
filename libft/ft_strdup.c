/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zchoo <zchoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 14:10:09 by zchoo             #+#    #+#             */
/*   Updated: 2025/11/27 14:43:49 by zchoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	char	*dest;
	int		dest_len;
	int		i;

	dest_len = ft_strlen(src) + 1;
	dest = malloc(dest_len);
	if (!dest)
		return (NULL);
	i = 0;
	while (i < dest_len)
	{
		dest[i] = src[i];
		i++;
	}
	return (dest);
}

/* #include <stdio.h>
int main(void)
{
	char *src;

	src = "Aaa";
	printf("src: %s, dest: %s\n", src, ft_strdup(src));
} */