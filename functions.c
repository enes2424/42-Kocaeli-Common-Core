/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eates <eates@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 11:10:32 by eates             #+#    #+#             */
/*   Updated: 2023/07/26 19:01:05 by eates            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	s(t_list *stack)
{
	int	tmp;

	if (ft_lstsize(stack) < 2)
		return ;
	tmp = get(stack, 0);
	set(stack, 0, get(stack, 1));
	set(stack, 1, tmp);
}

int	p(t_list **stack1, t_list **stack2)
{
	if (!*stack2)
		return (0);
	if (push(stack1, pop(stack2)) == -1)
		return (-1);
	return (1);
}

void	r(t_list *stack)
{
	int	tmp;
	int	i;
	int	len;

	if (!stack)
		return ;
	tmp = get(stack, 0);
	i = 0;
	len = ft_lstsize(stack);
	while (++i < len)
		set(stack, i - 1, get(stack, i));
	set(stack, i - 1, tmp);
}

void	rr(t_list *stack)
{
	int	tmp;
	int	i;

	if (!stack)
		return ;
	tmp = get(stack, ft_lstsize(stack) - 1);
	i = ft_lstsize(stack);
	while (--i > 0)
	{
		set(stack, i, get(stack, i - 1));
	}
	set(stack, 0, tmp);
}

int	min(t_list *stack)
{
	int	min;
	int	index;
	int	tmp;
	int	len;

	if (!stack)
		return (0);
	index = 0;
	min = get(stack, 0);
	len = ft_lstsize(stack);
	while (--len > 0)
	{
		tmp = get(stack, len);
		if (min > tmp)
		{
			min = tmp;
			index = len;
		}
	}
	return (index);
}
