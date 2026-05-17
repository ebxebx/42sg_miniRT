/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zchoo <zchoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 19:34:40 by zchoo             #+#    #+#             */
/*   Updated: 2025/11/27 14:24:57 by zchoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*dst_b;
	unsigned char	*src_b;
	size_t			i;

	dst_b = (unsigned char *) dest;
	src_b = (unsigned char *) src;
	i = 0;
	while (i < n)
	{
		if (src_b < dst_b && src_b + n >= dst_b)
			*(dst_b + n - i - 1) = *(src_b + n - i - 1);
		else
			*(dst_b + i) = *(src_b + i);
		i++;
	}
	return (dest);
}
