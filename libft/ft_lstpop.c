/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zchoo <zchoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 18:13:31 by zchoo             #+#    #+#             */
/*   Updated: 2025/12/27 18:35:51 by zchoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstpop(t_list **lst)
{
	t_list	*node;

	if (!lst || !*lst)
		return (NULL);
	node = *lst;
	*lst = (*lst)->next;
	node->next = NULL;
	return (node);
}
