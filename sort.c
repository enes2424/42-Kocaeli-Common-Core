/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eates <eates@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 13:57:55 by eates             #+#    #+#             */
/*   Updated: 2023/08/06 15:20:02 by eates            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sort_array(int *sorted_array, int size)
{
	int	i;
	int	j;
	int	tmp;

	i = 0;
	while (i < size - 1)
	{
		j = i + 1;
		while (j < size)
		{
			if (sorted_array[i] > sorted_array[j])
			{
				tmp = sorted_array[i];
				sorted_array[i] = sorted_array[j];
				sorted_array[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

void	basic_sort(t_push_swap	*p)
{
	p->b = 0;
	function(p->a);
	while (!is_it_in_order(p->a))
	{
		p_operations(p, &(p->b), &(p->a), 0);
		function(p->a);
	}
	while (p->b)
		p_operations(p, &(p->a), &(p->b), 1);
}

void	sort_three_arg(t_list **a)
{
	if (!max(*a))
	{
		r(*a);
		ft_printf("ra\n");
	}
	if (max(*a) == 1)
	{
		rr(*a);
		ft_printf("rra\n");
	}
	if (min(*a))
	{
		s(*a);
		ft_printf("sa\n");
	}
}

int	get_middle(int *pivot, t_list *a, int size)
{
	int		i;
	int		*tmp;

	tmp = (int *)malloc(sizeof(int) * size);
	if (!tmp)
		return (0);
	i = -1;
	while (++i < size)
		tmp[i] = get(a, i);
	sort_array(tmp, size);
	*pivot = tmp[size / 2];
	free(tmp);
	return (1);
}

int	is_sorted(t_list *stack, char c, int len)
{
	if (c == 'a')
	{
		while (--len)
			if (get(stack, len) < get(stack, len - 1))
				return (0);
	}
	else
	{
		while (--len)
			if (get(stack, len) > get(stack, len - 1))
				return (0);
	}
	return (1);
}
