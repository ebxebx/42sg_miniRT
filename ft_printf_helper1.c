/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_helper1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zchoo <zchoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 08:57:07 by zchoo             #+#    #+#             */
/*   Updated: 2026/01/02 14:51:37 by zchoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	*ft_put_hex_str(unsigned long long num, int to_upper)
{
	int					len;
	unsigned long long	temp;
	char				*hex_chars;
	char				*hex_str;

	hex_chars = "0123456789abcdef";
	if (to_upper)
		hex_chars = "0123456789ABCDEF";
	len = 1;
	temp = num;
	while (temp >= 16)
	{
		temp /= 16;
		len++;
	}
	hex_str = ft_calloc(sizeof(char), len + 1);
	if (!hex_str)
		return (NULL);
	while (len > 0)
	{
		hex_str[len - 1] = hex_chars[num % 16];
		num /= 16;
		len--;
	}
	return (hex_str);
}

void	*ft_put_addr(void *addr, char *pad_left, char *post_fix)
{
	char				*hex_str;
	char				*temp;
	int					len;

	temp = ft_put_hex_str((unsigned long long)addr, 0);
	if (!temp)
		return (NULL);
	len = ft_strlen(pad_left) + ft_strlen(temp) + ft_strlen(post_fix) + 1;
	hex_str = ft_calloc(sizeof(char), len);
	if (!hex_str)
	{
		free(temp);
		return (NULL);
	}
	ft_strlcat(hex_str, pad_left, len);
	ft_strlcat(hex_str, temp, len);
	ft_strlcat(hex_str, post_fix, len);
	free(temp);
	return (hex_str);
}

int	get_nbr_length(long l)
{
	int		len;

	len = 1;
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

void	ft_putnbr2_fd(long nbr_l, int fd)
{
	if (nbr_l < 0)
	{
		ft_putchar_fd('-', fd);
		nbr_l = -nbr_l;
	}
	if (nbr_l >= 10)
	{
		ft_putnbr2_fd(nbr_l / 10, fd);
		ft_putchar_fd('0' + (nbr_l % 10), fd);
	}
	else
		ft_putchar_fd('0' + nbr_l, fd);
}
