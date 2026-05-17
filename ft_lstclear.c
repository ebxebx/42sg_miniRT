/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zchoo <zchoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 12:48:08 by zchoo             #+#    #+#             */
/*   Updated: 2025/12/27 18:36:03 by zchoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*node;
	t_list	*temp;

	node = *lst;
	while (node && node->next)
	{
		temp = node->next;
		ft_lstdelone(node, del);
		node = temp;
	}
	if (node)
		ft_lstdelone(node, del);
	node = NULL;
	*lst = NULL;
}
