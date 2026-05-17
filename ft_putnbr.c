/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zchoo <zchoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 17:13:51 by zchoo             #+#    #+#             */
/*   Updated: 2025/11/27 14:25:32 by zchoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>

void	ft_putnbr(int nb)
{
	char	c;

	if (nb == INT_MIN)
	{
		ft_putnbr(nb / 10);
		ft_putnbr(((nb / 10 * 10) + nb));
	}
	else
	{
		if (nb < 0)
		{
			write(1, "-", 1);
			nb *= -1;
		}
		if (nb >= 10)
			ft_putnbr(nb / 10);
		c = (nb % 10) + '0';
		write(1, &c, 1);
	}
}

// #include <stdio.h>
// int main(void)
// {
// 	ft_putnbr(123);
// 	printf("\n");
// 	ft_putnbr(100);
// 	printf("\n");
// 	ft_putnbr(10);
// 	printf("\n");
// 	ft_putnbr(-10);
// 	printf("\n");
// 	ft_putnbr(-100000);
// 	printf("\n");
// 	ft_putnbr(-2147483648);
// 	printf("\n");
// 	return 1;
// }