/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_other_functions.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eates <eates@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 20:22:26 by eates             #+#    #+#             */
/*   Updated: 2023/08/06 21:54:03 by eates            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdlib.h>

void	error(t_push_swap	*p)
{
	ft_lstclear(&(p->a), &del);
	ft_lstclear(&(p->b), &del);
	if (p->change_argv)
		free_string_array(p->arr);
	return (ft_printf("\033[0;33mError\n"), exit(1));
}

void	p_operations(t_push_swap *pu, t_list **a, t_list **b, int x)
{
	if (p(a, b) == -1)
		error(pu);
	if (x == 1)
		ft_printf("pa\n");
	else
		ft_printf("pb\n");
}

void	s_operations(t_push_swap *p, char c)
{
	if (c == 'a')
	{
		s(p->a);
		ft_printf("sa\n");
	}
	else
	{
		s(p->b);
		ft_printf("sb\n");
	}
}

void	r_operations(t_push_swap *p, char c)
{
	if (c == 'a')
	{
		r(p->a);
		ft_printf("ra\n");
	}
	else
	{
		r(p->b);
		ft_printf("rb\n");
	}
}

void	rr_operations(t_push_swap *p, char c)
{
	if (c == 'a')
	{
		rr(p->a);
		ft_printf("rra\n");
	}
	else
	{
		rr(p->b);
		ft_printf("rrb\n");
	}
}
