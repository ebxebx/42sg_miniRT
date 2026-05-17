/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ka-tan <ka-tan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 14:10:09 by zchoo             #+#    #+#             */
/*   Updated: 2026/03/28 20:45:42 by ka-tan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *str, size_t n)
{
	char	*copy;
	size_t	i;

	if (!str)
		return (NULL);
	copy = (char *)malloc(sizeof(char) * (n + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < n && str[i])
	{
		copy[i] = str[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}

// #include <stdio.h>
// int main(void)
// {
// 	char 	*src;
// 	size_t	n;

// 	n = 6;
// 	src = "Aaa";
// 	printf("src: %s, dest: %s\n", src, ft_strndup(src, n));
// }