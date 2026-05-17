/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zchoo <zchoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 16:02:24 by zchoo             #+#    #+#             */
/*   Updated: 2026/03/30 21:17:18 by zchoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
# include "libft.h"

int		ft_printf(const char *fmt, ...);
int		ft_dprintf(int fd, const char *fmt, ...);
int		ft_vprintf(const char *fmt, va_list *args);
int		ft_vdprintf(int fd, const char *fmt, va_list *args);
void	*ft_put_hex_str(unsigned long long num, int to_upper);
void	*ft_put_addr(void *addr, char *pad_left, char *post_fix);
void	ft_putnbr2_fd(long nbr_l, int fd);
int		get_nbr_length(long l);

int		handle_flag(int fd, va_list *ap, const char flag);
int		handle_text(int fd, va_list *ap, const char flag);
int		handle_pointer(int fd, va_list *ap, const char flag);
int		handle_hexadecimal(int fd, va_list *ap, const char flag);
int		handle_signed_number(int fd, va_list *ap, const char flag);
int		handle_unsigned_number(int fd, va_list *ap, const char flag);
int		handle_number(int fd, va_list *ap, const char flag);
int		handle_floating_point_number(int fd, va_list *ap, const char flag);

#endif
