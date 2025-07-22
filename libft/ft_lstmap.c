/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnemor <lnemor@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 15:04:38 by lnemor            #+#    #+#             */
/*   Updated: 2021/11/15 16:43:59 by lnemor           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newlist;
	t_list	*newelement;

	(void)del;
	if (!lst || !f)
		return (NULL);
	newlist = NULL;
	while (lst != NULL)
	{
		newelement = ft_lstnew((*f)(lst->content));
		ft_lstadd_back(&newlist, newelement);
		lst = lst->next;
	}
	return (newlist);
}
