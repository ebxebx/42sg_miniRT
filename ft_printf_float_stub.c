/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_float_stub.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zchoo <zchoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/29 19:16:00 by zchoo             #+#    #+#             */
/*   Updated: 2026/03/30 21:16:11 by zchoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	handle_floating_point_number(int fd, va_list *ap, const char flag)
{
	(void)fd;
	if (flag == 'f')
		(void)va_arg(*ap, double);
	return (0);
}
