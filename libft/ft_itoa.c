/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zchoo <zchoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 18:34:31 by zchoo             #+#    #+#             */
/*   Updated: 2025/11/27 14:24:25 by zchoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_nbr_length(int n)
{
	int		len;
	long	l;

	len = 1;
	l = n;
	if (l < 0)
	{
		l = -l;
		len++;
	}
	while (l >= 10)
	{
		l /= 10;
		len++;
	}
	return (len);
}

static void	fill_nbr_to_arr(char *nbr, int len, int n)
{
	int		i;
	int		offset;
	long	l;

	i = 0;
	offset = 1;
	l = n;
	if (l < 0)
	{
		nbr[i] = '-';
		l = -l;
		i++;
		offset = 0;
	}
	while (i < len)
	{
		nbr[len - i - offset] = '0' + (l % 10);
		l /= 10;
		i++;
	}
	nbr[len] = 0;
}

char	*ft_itoa(int n)
{
	int		len;
	char	*nbr;

	len = get_nbr_length(n);
	nbr = malloc(sizeof(char) * (len + 1));
	if (!nbr)
		return (NULL);
	fill_nbr_to_arr(nbr, len, n);
	return (nbr);
}
