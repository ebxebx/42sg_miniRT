/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zchoo <zchoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 16:03:42 by zchoo             #+#    #+#             */
/*   Updated: 2025/11/27 14:47:08 by zchoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*dst_b;
	unsigned char	*src_b;
	size_t			i;

	dst_b = (unsigned char *) dest;
	src_b = (unsigned char *) src;
	i = 0;
	while (i < n)
	{
		dst_b[i] = src_b[i];
		i++;
	}
	return (dest);
}
