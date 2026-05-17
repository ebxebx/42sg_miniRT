/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zchoo <zchoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 11:53:27 by zchoo             #+#    #+#             */
/*   Updated: 2025/11/27 14:26:55 by zchoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_char_in_set(const char c, const char *set)
{
	char	*set2;

	set2 = (char *)set;
	while (*set2)
	{
		if (*set2 == (char)c)
			return (1);
		set2++;
	}
	return (0);
}

char	*ft_strtrim(const char *s1, const char *set)
{
	int	start;
	int	end;

	start = 0;
	end = ft_strlen(s1);
	if (end > 0)
		end--;
	while (s1[start] && is_char_in_set(s1[start], set))
		start++;
	while (s1[end] && is_char_in_set(s1[end], set))
		end--;
	if (end < start)
		return (ft_calloc(1, 1));
	return (ft_substr(s1, start, end - start + 1));
}

/* int main(void)
{
	char s[100] = {0};

	ft_strlcpy(s, "", sizeof(s));
	printf("strtrim = %s\n", ft_strtrim(s, " \n"));

	ft_strlcpy(s, "   ", sizeof(s));
	printf("strtrim = %s\n", ft_strtrim(s, " \n"));
	return 0;
} */