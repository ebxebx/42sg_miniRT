/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zchoo <zchoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 20:36:02 by zchoo             #+#    #+#             */
/*   Updated: 2025/11/27 14:12:42 by zchoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t size)
{
	int				cmp_rst;
	unsigned int	i;

	if (*to_find == '\0')
		return ((char *)str);
	if (*str == '\0')
		return (NULL);
	cmp_rst = -1;
	i = 0;
	while (i < size && ft_strlen(to_find) <= size - i)
	{
		cmp_rst = ft_strncmp(str + i, to_find, ft_strlen(to_find));
		if (cmp_rst == 0)
			return ((char *)str + i);
		i++;
	}
	return (NULL);
}
// without use ft_strncmp
/* char	*ft_strnstr(char *str, char *to_find, unsigned int size)
{
	int				found;
	unsigned int	i;
	unsigned int	j;

	if (*to_find == '\0')
		return (str);
	found = -1;
	i = 0;
	while (str[i] != 0 && i < size)
	{
		j = 0;
		while (j < ft_strlen(to_find) && (i + j <= size - 1)
			&& str[i + j] && (str[i + j] == to_find[j]))
			j++;
		if (j == ft_strlen(to_find))
		{
			found = 1;
			break ;
		}
		i++;
	}
	if (found > 0)
		return (&str[i]);
	else
		return (NULL);
} */
