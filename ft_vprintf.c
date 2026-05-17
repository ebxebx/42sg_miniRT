/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zchoo <zchoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 16:13:15 by zchoo             #+#    #+#             */
/*   Updated: 2026/03/30 21:17:40 by zchoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_vdprintf(int fd, const char *fmt, va_list *args)
{
	size_t	cnt;

	cnt = 0;
	while (*fmt)
	{
		if (*fmt == '%')
		{
			fmt++;
			cnt += handle_flag(fd, args, *fmt);
		}
		else
		{
			ft_putchar_fd(*fmt, fd);
			cnt++;
		}
		fmt++;
	}
	return (cnt);
}

int	ft_vprintf(const char *fmt, va_list *args)
{
	return (ft_vdprintf(STDOUT_FILENO, fmt, args));
}

/* int main(void)
{
	ft_printf("", 1, 2, 3);
	return (0);
} */
