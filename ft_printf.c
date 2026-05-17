/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zchoo <zchoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 16:13:15 by zchoo             #+#    #+#             */
/*   Updated: 2026/03/30 21:16:03 by zchoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
• %c Prints a single character.
• %s Prints a string (as defined by the common C convention).
• %p The void * pointer argument has to be printed in hexadecimal format.
• %d Prints a decimal (base 10) number.
• %i Prints an integer in base 10.
• %u Prints an unsigned decimal (base 10) number.
• %x Prints a number in hexadecimal (base 16) lowercase format.
• %X Prints a number in hexadecimal (base 16) uppercase format.
• %% Prints a percent sign.
*/

int	handle_text(int fd, va_list *ap, const char flag)
{
	size_t	cnt;
	char	*s;

	cnt = 0;
	if (flag == 'c')
	{
		ft_putchar_fd((char)va_arg(*ap, int), fd);
		cnt++;
	}
	else if (flag == 's')
	{
		s = va_arg(*ap, char *);
		if (!s)
			s = "(null)";
		ft_putstr_fd(s, fd);
		cnt += ft_strlen(s);
	}
	return ((int)cnt);
}

int	handle_pointer(int fd, va_list *ap, const char flag)
{
	size_t			cnt;
	void			*ptr;
	char			*addr_str;
	const char		*prefix;

	cnt = 0;
	if (flag == 'p')
	{
		prefix = "0x";
		ptr = va_arg(*ap, void *);
		if (!ptr)
		{
			ft_putstr_fd("(nil)", fd);
			return (5);
		}
		addr_str = ft_put_addr(ptr, (char *)prefix, "");
		if (!addr_str)
			return (0);
		ft_putstr_fd(addr_str, fd);
		cnt += ft_strlen(addr_str);
		free(addr_str);
	}
	return (cnt);
}

int	handle_flag(int fd, va_list *ap, const char flag)
{
	size_t	cnt;

	cnt = 0;
	if (flag == 'c' || flag == 's')
		cnt += handle_text(fd, ap, flag);
	else if (flag == 'p')
		cnt += handle_pointer(fd, ap, flag);
	else if (ft_strchr("dfiuxXf", flag))
		cnt += handle_number(fd, ap, flag);
	else if (flag == '%')
	{
		ft_putchar_fd(flag, fd);
		cnt++;
	}
	return (cnt);
}

int	ft_dprintf(int fd, const char *fmt, ...)
{
	va_list	ap;
	int		cnt;

	va_start(ap, fmt);
	cnt = ft_vdprintf(fd, fmt, &ap);
	va_end(ap);
	return (cnt);
}

int	ft_printf(const char *fmt, ...)
{
	va_list	ap;
	int		cnt;

	va_start(ap, fmt);
	cnt = ft_vdprintf(STDOUT_FILENO, fmt, &ap);
	va_end(ap);
	return (cnt);
}

/* int main(void)
{
	ft_printf("", 1, 2, 3);
	return (0);
} */
