/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zchoo <zchoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 11:01:14 by zchoo             #+#    #+#             */
/*   Updated: 2026/04/08 16:34:28 by zchoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_decimal(double *decimal_place, char **str)
{
	if (*decimal_place == 1.0 && ft_isdigit(*(*str + 1)))
	{
		*decimal_place = 0.1;
		(*str)++;
	}
	else
		return (0);
	return (1);
}

double	ft_extract_and_convert(char *str)
{
	double	final_num;
	int		base;
	double	decimal_place;

	final_num = 0;
	base = 10;
	decimal_place = 1.0;
	while (*str && (ft_isdigit(*str) || *str == '.'))
	{
		if (*str == '.' && check_decimal(&decimal_place, &str))
			continue ;
		else if ((*str == '.') && !check_decimal(&decimal_place, &str))
			break ;
		final_num *= base;
		final_num += (*str - '0');
		str++;
		if (decimal_place <= 0.1)
			decimal_place *= 0.1;
	}
	if (decimal_place < 1.0)
		decimal_place *= 10;
	return (final_num * decimal_place);
}

double	ft_atof(const char *str_)
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

/* #include <stdio.h>
#include <stdlib.h>

int	main(void)
{
	printf("%f\n", ft_atof(" \n\t \v\r\f   219"));
	printf("*  %f\n", atof(" \n\t \v\r\f   219"));
	printf("%f\n", ft_atof("   219"));
	printf("*  %f\n", atof("   219"));
	printf("%f\n", ft_atof("   219.123"));
	printf("*  %f\n", atof("   219.123"));
	printf("%f\n", ft_atof("   219.12.3"));
	printf("*  %f\n", atof("   219.12.3"));
	printf("%f\n", ft_atof("   219."));
	printf("*  %f\n", atof("   219."));
	printf("%f\n", ft_atof("   219.."));
	printf("*  %f\n", atof("   219.."));
	printf("%f\n", ft_atof("   219..1"));
	printf("*  %f\n", atof("   219..1"));
	printf("%f\n", ft_atof("   +219"));
	printf("*  %f\n", atof("   +219"));
	printf("%f\n", ft_atof("   -219"));
	printf("*  %f\n", atof("   -219"));
	printf("%f\n", ft_atof("   --219"));
	printf("*  %f\n", atof("   --219"));
	printf("%f\n", ft_atof("   -=-219"));
	printf("*  %f\n", atof("   -=-219"));
	printf("%f\n", ft_atof("   -+-219"));
	printf("*  %f\n", atof("   -+-219"));
	printf("%f\n", ft_atof("   -+-21 9"));
	printf("*  %f\n", atof("   -+-21 9"));
	printf("%f\n", ft_atof(""));
	printf("*  %f\n", atof(""));
	return (0);
}
*/
