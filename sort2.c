/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eates <eates@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 15:47:27 by eates             #+#    #+#             */
/*   Updated: 2023/08/26 15:47:28 by eates            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	quicksort_3a(t_list	*stack, int len)
{
	while (len == 2 || !is_sorted(stack, 'a', 3))
	{
		if (get(stack, 0) > get(stack, 1))
		{
			s(stack);
			ft_printf("sa\n");
		}
		else if (len == 3)
		{
			r(stack);
			ft_printf("ra\n");
			s(stack);
			ft_printf("sa\n");
			rr(stack);
			ft_printf("rra\n");
		}
		if (len == 2)
			return ;
	}
}

static int	ft_push(t_push_swap *p, int len, int operation)
{
	if (operation == 0)
		p_operations(p, &(p->b), &(p->a), 0);
	else
		p_operations(p, &(p->a), &(p->b), 1);
	return (--len);
}

static void	quicksort_3b(t_push_swap *p, int len)
{
	if (len == 1)
		p_operations(p, &(p->a), &(p->b), 1);
	else if (len == 2)
	{
		if (get(p->b, 0) < get(p->b, 1))
			s_operations(p, 'b');
		while (len--)
			p_operations(p, &(p->a), &(p->b), 1);
	}
	else if (len == 3)
	{
		while (len
			|| !(get(p->a, 0) < get(p->a, 1) && get(p->a, 1) < get(p->a, 2)))
		{
			if (len == 1 && get(p->a, 0) > get(p->a, 1))
				s_operations(p, 'a');
			else if (len == 1 || (len >= 2 && get(p->b, 0) > get(p->b, 1))
				|| (len == 3 && get(p->b, 0) > get(p->b, 2)))
				len = ft_push(p, len, 1);
			else
				s_operations(p, 'b');
		}
	}
	return ;
}

int	quicksort_a(t_push_swap *p, int len, int count)
{
	int	pivot;
	int	items;

	if (is_sorted(p->a, 'a', len))
		return (1);
	items = len;
	if (len <= 3)
	{
		if (ft_lstsize(p->a) == 3)
			return (sort_three_arg(&(p->a)), 1);
		return (quicksort_3a(p->a, len), 1);
	}
	if (!get_middle(&pivot, p->a, len))
		return (0);
	while (len != items / 2 + items % 2)
	{
		if (get(p->a, 0) < pivot && (len--))
			p_operations(p, &(p->b), &(p->a), 0);
		else if (++count)
			r_operations(p, 'a');
	}
	while (items / 2 + items % 2 != ft_lstsize(p->a) && count--)
		rr_operations(p, 'a');
	return (quicksort_a(p, items / 2 + items % 2, 0)
		&& quicksort_b(p, items / 2, 0));
}

int	quicksort_b(t_push_swap *p, int len, int count)
{
	int	pivot;
	int	items;

	if (!count && is_sorted(p->b, 'b', len))
		while (len--)
			p_operations(p, &(p->a), &(p->b), 1);
	if (len <= 3)
		return (quicksort_3b(p, len), 1);
	items = len;
	if (!get_middle(&pivot, p->b, len))
		return (0);
	while (len != items / 2)
	{
		if (get(p->b, 0) >= pivot && len--)
			p_operations(p, &(p->a), &(p->b), 1);
		else if (++count)
			r_operations(p, 'b');
	}
	while (items / 2 != ft_lstsize(p->b) && count--)
		rr_operations(p, 'b');
	return (quicksort_a(p, items / 2 + items % 2, 0)
		&& quicksort_b(p, items / 2, 0));
}
