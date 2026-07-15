/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_float.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zchoo <zchoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/29 19:05:00 by zchoo             #+#    #+#             */
/*   Updated: 2026/07/15 18:39:03 by zchoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <math.h>

int	handle_floating_point_number(int fd, va_list *ap, const char flag)
{
	size_t	cnt;
	double	int_part;
	double	frac_part;
	int		frac_len;

	cnt = 0;
	if (flag == 'f')
	{
		frac_part = rint(modf(va_arg(*ap, double), &int_part) * 1000000);
		if (frac_part < 0.0)
			frac_part *= -1.0;
		ft_putnbr_fd(int_part, fd);
		cnt += get_nbr_length((long)int_part);
		ft_putchar_fd('.', fd);
		cnt++;
		frac_len = get_nbr_length((long)frac_part);
		if (frac_len < 6)
			write(fd, "000000", 6 - frac_len);
		ft_putnbr_fd(frac_part, fd);
		cnt += frac_len;
	}
	return (cnt);
}
