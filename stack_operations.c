/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eates <eates@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 16:35:42 by eates             #+#    #+#             */
/*   Updated: 2023/07/20 16:40:06 by eates            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdlib.h>

void	del(void *content)
{
	free(content);
}

int	push(t_list **stack, int content)
{
	int		*i;
	t_list	*new;

	i = malloc(sizeof(int));
	if (!i)
		return (-1);
	*i = content;
	new = ft_lstnew(i);
	if (!new)
		return (-1);
	ft_lstadd_back(stack, new);
	return (1);
}

int	pop(t_list **stack)
{
	t_list	*tmp;
	t_list	*tmp_last;
	int		content;

	if (!*stack)
		return (0);
	tmp_last = ft_lstlast(*stack);
	if (!(*stack)->next)
	{
		content = *((int *)(*stack)->content);
		return (ft_lstdelone(*stack, &del), *stack = NULL, content);
	}
	tmp = *stack;
	while (tmp->next->next)
		tmp = tmp->next;
	tmp->next = NULL;
	content = *((int *)tmp_last->content);
	ft_lstdelone(tmp_last, &del);
	return (content);
}

int	get(t_list *stack, int index)
{
	if (index >= ft_lstsize(stack))
		return (0);
	index = ft_lstsize(stack) - index - 1;
	while (index--)
		stack = stack->next;
	return (*((int *)stack->content));
}

void	set(t_list *stack, int index, int new_content)
{
	if (index >= ft_lstsize(stack))
		return ;
	index = ft_lstsize(stack) - index - 1;
	while (index--)
		stack = stack->next;
	*((int *)stack->content) = new_content;
}
