/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zchoo <zchoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 18:24:25 by zchoo             #+#    #+#             */
/*   Updated: 2026/04/08 16:34:10 by zchoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>

static long	ft_extract_and_convert(char *str)
{
	long	final_num;
	long	backup;
	int		base;

	final_num = 0;
	backup = 0;
	base = 10;
	while (*str && (ft_isdigit(*str)))
	{
		final_num *= base;
		final_num += (*str - '0');
		str++;
		if (final_num < backup)
			return (LONG_MAX);
		backup = final_num;
	}
	return (final_num);
}

long	ft_atol(const char *str_)
{
	int		sign;
	long	converted;
	char	*str;

	sign = 1;
	str = (char *)str_;
	while (ft_isspace(*str))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	if (!ft_isdigit(*str))
		return (0);
	converted = ft_extract_and_convert(str);
	if (sign == -1 && converted == LONG_MAX)
		return (LONG_MIN);
	return (converted * sign);
}

/* #include <stdio.h>
#include <stdlib.h>
#include "limits.h"
int	main(void)
{
	printf("%ld\n", ft_atol(" \n\t \v\r\f   219"));
	printf("*  %ld\n", atol(" \n\t \v\r\f   219"));

	printf("%ld\n", ft_atol("   -9223372036854775900"));
	printf("*  %li\n", atol("   -9223372036854775900"));
	printf("%ld\n", ft_atol("   9223372036854775808"));
	printf("*  %li\n", atol("   9223372036854775808"));
	printf("%ld\n", ft_atol("   18446744073709551616"));
	printf("*  %li\n", atol("   18446744073709551616"));
	printf("%li\n", ft_atol("   219888888888888888888888888888888"));
	printf("*  %li\n", atol("   219888888888888888888888888888888"));
	printf("LONG_MAX:  %lli\n", LONG_MAX);
	printf("LLONG_MAX:  %lli\n", LLONG_MAX);

	// printf("%ld\n", ft_atol("   +219"));
	// printf("*  %ld\n", atol("   +219"));

	// printf("%ld\n", ft_atol("   -219"));
	// printf("*  %ld\n", atol("   -219"));

	// printf("%ld\n", ft_atol("   --219"));
	// printf("*  %ld\n", atol("   --219"));

	// printf("%ld\n", ft_atol("   -=-219"));
	// printf("*  %ld\n", atol("   -=-219"));

	// printf("%ld\n", ft_atol("   -+-219"));
	// printf("*  %ld\n", atol("   -+-219"));

	// printf("%ld\n", ft_atol("   -+-21 9"));
	// printf("*  %ld\n", atol("   -+-21 9"));

	// printf("%ld\n", ft_atol(""));
	// printf("*  %ld\n", atol(""));
	return (0);
} */