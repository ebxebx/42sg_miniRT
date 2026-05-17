/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zchoo <zchoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 15:19:15 by zchoo             #+#    #+#             */
/*   Updated: 2025/11/27 14:45:32 by zchoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*bytes1;
	unsigned char	*bytes2;
	size_t			i;
	int				cmp_rst;

	bytes1 = (unsigned char *) s1;
	bytes2 = (unsigned char *) s2;
	i = 0;
	cmp_rst = 0;
	while (i < n && cmp_rst == 0)
	{
		cmp_rst = *bytes1 - *bytes2;
		if (cmp_rst)
			return (cmp_rst);
		bytes1++;
		bytes2++;
		i++;
	}
	return (0);
}
