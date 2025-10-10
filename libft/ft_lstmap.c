/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eates <eates@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 17:43:37 by eates             #+#    #+#             */
/*   Updated: 2023/07/07 10:38:30 by eates            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*ret;
	t_list	*tmp;
	void	*content;

	if (!f || !del)
		return (NULL);
	ret = NULL;
	while (lst)
	{
		content = f(lst->content);
		if (!content)
			return (ft_lstclear(&ret, del), NULL);
		tmp = ft_lstnew(content);
		if (!tmp)
			return (del(content), ft_lstclear(&ret, del), NULL);
		ft_lstadd_back(&ret, tmp);
		lst = lst->next;
	}
	return (ret);
}
