/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_helper2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zchoo <zchoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 14:00:11 by zchoo             #+#    #+#             */
/*   Updated: 2026/03/30 21:16:43 by zchoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	handle_hexadecimal(int fd, va_list *ap, const char flag)
{
	size_t			cnt;
	unsigned int	num;
	char			*hex_str;
	int				to_upper;

	cnt = 0;
	to_upper = 0;
	if (flag == 'X')
		to_upper = 1;
	num = va_arg(*ap, unsigned int);
	if (num == 0)
	{
		ft_putchar_fd('0', fd);
		return (1);
	}
	hex_str = ft_put_hex_str((unsigned long long)num, to_upper);
	if (!hex_str)
		return (0);
	ft_putstr_fd(hex_str, fd);
	cnt += ft_strlen(hex_str);
	free(hex_str);
	return (cnt);
}

int	handle_signed_number(int fd, va_list *ap, const char flag)
{
	size_t	cnt;
	int		d;

	cnt = 0;
	if (flag == 'd' || flag == 'i')
	{
		d = va_arg(*ap, int);
		ft_putnbr_fd(d, fd);
		cnt += get_nbr_length(d);
	}
	return (cnt);
}

int	handle_unsigned_number(int fd, va_list *ap, const char flag)
{
	size_t			cnt;
	unsigned int	u;

	cnt = 0;
	if (flag == 'u')
	{
		u = va_arg(*ap, unsigned int);
		ft_putnbr2_fd(u, fd);
		cnt += get_nbr_length(u);
	}
	return (cnt);
}

int	handle_number(int fd, va_list *ap, const char flag)
{
	size_t	cnt;

	cnt = 0;
	if (flag == 'd' || flag == 'i')
		cnt += handle_signed_number(fd, ap, flag);
	else if (flag == 'u')
		cnt += handle_unsigned_number(fd, ap, flag);
	else if (flag == 'x' || flag == 'X')
		cnt += handle_hexadecimal(fd, ap, flag);
	else if (flag == 'f')
		cnt += handle_floating_point_number(fd, ap, flag);
	return (cnt);
}
