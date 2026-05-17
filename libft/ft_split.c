/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ka-tan <ka-tan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 19:31:24 by zchoo             #+#    #+#             */
/*   Updated: 2026/03/28 20:42:19 by ka-tan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_words(char *str, char c)
{
	int	count;

	count = 0;
	while (*str)
	{
		while (*str == c)
			str++;
		if (*str == '\0')
			break ;
		while (*str && *str != c)
			str++;
		count++;
	}
	return (count);
}

// static char	*ft_strndup(char *str, int n)
// {
// 	char	*copy;
// 	int		i;

// 	if (!(*str))
// 		return (NULL);
// 	copy = malloc(sizeof(char) * (n + 1));
// 	if (!copy)
// 		return (NULL);
// 	i = 0;
// 	while (str[i] && i < n)
// 	{
// 		copy[i] = str[i];
// 		i++;
// 	}
// 	copy[i] = '\0';
// 	return (copy);
// }

static void	free_array(char **arr, size_t n)
{
	while (n > 0)
		free(arr[--n]);
	free(arr);
}

static char	**split_to_array(char **arr, int words, char *str, char c)
{
	int		i;
	char	*start;

	i = 0;
	while (i < words)
	{
		while (*str == c)
			str++;
		if (*str == '\0')
			break ;
		start = str;
		while (*str && *str != c)
			str++;
		arr[i] = ft_strndup(start, str - start);
		if (!arr[i])
		{
			free_array(arr, i);
			return (NULL);
		}
		i++;
	}
	arr[i] = NULL;
	return (arr);
}

char	**ft_split(const char *str, char c)
{
	char	**arr;
	int		words;
	char	*str2;

	str2 = (char *)str;
	words = ft_count_words(str2, c);
	arr = (char **)malloc(sizeof(char *) * (words + 1));
	if (!arr)
		return (NULL);
	return (split_to_array(arr, words, str2, c));
}

/* #include <stdio.h>
int main(void)
{
	char *str = "Ao0  Ba CU1 !\nDohoho";
	printf("count words: %d\n", ft_count_words(str, " \n"));
	char *new;
	new = ft_strndup(str, ft_strlen(str));
	if (new != NULL)
	{
		printf("New: %s\n", new);
		free(new);
	}

	char **arr = ft_split(str, " \n");
	if (arr != NULL)
	{
		for (int i = 0; arr[i] != NULL; i++)
		{
			printf("arr[%d]: %s\n", i, arr[i]);
			free(arr[i]);
		}
		free(arr);
	}

	str = "aaabbbaaaccc";
	printf("count words: %d\n", ft_count_words(str, " \n"));
	new = ft_strndup(str, ft_strlen(str));
	if (new != NULL)
	{
		printf("New: %s\n", new);
		free(new);
	}
	arr = ft_split(str, "ab");
	if (arr != NULL)
	{
		for (int i = 0; arr[i] != NULL; i++)
		{
			printf("arr[%d]: %s\n", i, arr[i]);
			free(arr[i]);
		}
		free(arr);
	}
} */