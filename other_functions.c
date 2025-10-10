/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eates <eates@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 00:19:07 by eates             #+#    #+#             */
/*   Updated: 2023/08/06 21:53:51 by eates            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdlib.h>

int	max(t_list *stack)
{
	int	max;
	int	index;
	int	tmp;
	int	len;

	if (!stack)
		return (0);
	index = 0;
	max = get(stack, 0);
	len = ft_lstsize(stack);
	while (--len > 0)
	{
		tmp = get(stack, len);
		if (max < tmp)
		{
			max = tmp;
			index = len;
		}
	}
	return (index);
}

void	function(t_list *a)
{
	int	min_index;
	int	len;

	len = ft_lstsize(a);
	if (max(a) != 0 && get(a, 0) > get(a, 1))
	{
		s(a);
		ft_printf("sa\n");
	}
	min_index = min(a);
	while (min_index <= len / 2 && min_index--)
	{
		r(a);
		ft_printf("ra\n");
	}
	if (min_index > len / 2)
	{
		while (min_index++ < len)
		{
			rr(a);
			ft_printf("rra\n");
		}
	}
}

int	is_it_in_order(t_list *stack)
{
	int	i;
	int	len;

	i = -1;
	len = ft_lstsize(stack);
	while (++i < len - 1)
		if (get(stack, i) > get(stack, i + 1))
			return (0);
	return (1);
}

int	in_list(t_list *stack, int num)
{
	int	len;

	len = ft_lstsize(stack);
	while (--len > -1)
		if (get(stack, len) == num)
			return (1);
	return (0);
}

int	has_error_and_create_stack(t_push_swap	*p)
{
	int	i;
	int	j;

	i = -1;
	while (p->arr[++i])
	{
		j = -1;
		while (p->arr[i][++j])
			if (!ft_isdigit(p->arr[i][j]) &&
				p->arr[i][0] != '-' && p->arr[i][0] != '+')
				return (ft_printf("\033[0;33mError\n"), 1);
	}
	p->a = NULL;
	while (--i > -1)
	{
		j = ft_atoi(p->arr[i], p, &del);
		if (in_list(p->a, j) || push(&(p->a), j) == -1)
			return (error(p), 1);
	}
	return (p->b = NULL, 0);
}
