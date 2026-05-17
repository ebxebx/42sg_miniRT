/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zchoo <zchoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 16:17:45 by zchoo             #+#    #+#             */
/*   Updated: 2025/11/27 14:25:21 by zchoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int nbr, int fd)
{
	long	nbr_l;

	nbr_l = nbr;
	if (nbr_l < 0)
	{
		ft_putchar_fd('-', fd);
		nbr_l = -nbr_l;
	}
	if (nbr_l >= 10)
	{
		ft_putnbr_fd(nbr_l / 10, fd);
		ft_putchar_fd('0' + (nbr_l % 10), fd);
	}
	else
		ft_putchar_fd('0' + nbr_l, fd);
}
