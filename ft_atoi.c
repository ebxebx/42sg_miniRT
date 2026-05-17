/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zchoo <zchoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 18:24:25 by zchoo             #+#    #+#             */
/*   Updated: 2026/04/08 16:25:55 by zchoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_extract_and_convert(char *str)
{
	int	final_num;
	int	base;

	final_num = 0;
	base = 10;
	while (*str && (ft_isdigit(*str)))
	{
		final_num *= base;
		final_num += (*str - '0');
		str++;
	}
	return (final_num);
}

int	ft_atoi(const char *str_)
{
	int		sign;
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
	return (ft_extract_and_convert(str) * sign);
}

// #include <stdio.h>
// #include <stdlib.h>

// int	main(void)
// {
// 	printf("%d\n", ft_atoi(" \n\t \v\r\f   219"));
// 	printf("*  %d\n", atoi(" \n\t \v\r\f   219"));

// 	printf("%d\n", ft_atoi("   219"));
// 	printf("*  %d\n", atoi("   219"));

// 	printf("%d\n", ft_atoi("   +219"));
// 	printf("*  %d\n", atoi("   +219"));

// 	printf("%d\n", ft_atoi("   -219"));
// 	printf("*  %d\n", atoi("   -219"));

// 	printf("%d\n", ft_atoi("   --219"));
// 	printf("*  %d\n", atoi("   --219"));

// 	printf("%d\n", ft_atoi("   -=-219"));
// 	printf("*  %d\n", atoi("   -=-219"));

// 	printf("%d\n", ft_atoi("   -+-219"));
// 	printf("*  %d\n", atoi("   -+-219"));

// 	printf("%d\n", ft_atoi("   -+-21 9"));
// 	printf("*  %d\n", atoi("   -+-21 9"));

// 	printf("%d\n", ft_atoi(""));
// 	printf("*  %d\n", atoi(""));
// 	return (0);
// }
