/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zchoo <zchoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 14:31:48 by zchoo             #+#    #+#             */
/*   Updated: 2025/12/27 18:35:41 by zchoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*first;
	t_list	*node;
	void	*content;

	first = NULL;
	while (lst)
	{
		content = f(lst->content);
		node = ft_lstnew(content);
		if (node)
			ft_lstadd_back(&first, node);
		else
		{
			if (content)
				del(content);
			ft_lstclear(&first, del);
		}
		lst = lst->next;
	}
	return (first);
}
