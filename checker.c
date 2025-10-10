/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eates <eates@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 10:09:01 by eates             #+#    #+#             */
/*   Updated: 2023/08/06 21:54:41 by eates            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdlib.h>

static int	s_operation(t_push_swap *p, char **instruction)
{
	int	return_value;

	return_value = 0;
	if (!ft_strncmp(*instruction, "sa\n", 4)
		|| !ft_strncmp(*instruction, "ss\n", 4))
	{
		return_value = 1;
		s(p->a);
	}
	if (!ft_strncmp(*instruction, "sb\n", 4)
		|| !ft_strncmp(*instruction, "ss\n", 4))
	{
		return_value = 1;
		s(p->b);
	}
	return (return_value);
}

static int	r_operation(t_push_swap *p, char **instruction)
{
	int	return_value;

	return_value = 0;
	if (!ft_strncmp(*instruction, "ra\n", 4)
		|| !ft_strncmp(*instruction, "rr\n", 4))
	{
		return_value = 1;
		r(p->a);
	}
	if (!ft_strncmp(*instruction, "rb\n", 4)
		|| !ft_strncmp(*instruction, "rr\n", 4))
	{
		return_value = 1;
		r(p->b);
	}
	return (return_value);
}

static int	cmp_operations(t_push_swap *pu, char **instruction)
{
	if (s_operation(pu, instruction))
		return (0);
	if (!ft_strncmp(*instruction, "pa\n", 4))
		p(&(pu->a), &(pu->b));
	else if (!ft_strncmp(*instruction, "pb\n", 4))
		p(&(pu->b), &(pu->a));
	else if (r_operation(pu, instruction))
		return (0);
	else if (!ft_strncmp(*instruction, "rra\n", 5))
		rr(pu->a);
	else if (!ft_strncmp(*instruction, "rrb\n", 5))
		rr(pu->b);
	else if (!ft_strncmp(*instruction, "rrr\n", 5))
	{
		rr(pu->a);
		rr(pu->b);
	}
	else
		return (ft_printf("\033[0;33mError\n"), -1);
	return (0);
}

static int	operations(t_push_swap *p)
{
	char	*instruction;

	instruction = get_next_line(0);
	while (instruction)
	{
		if (cmp_operations(p, &instruction) == -1)
			return (free(instruction), 0);
		free(instruction);
		instruction = get_next_line(0);
	}
	if (is_it_in_order(p->a) && ft_lstsize(p->b) == 0)
	{
		ft_printf("\033[0;32mOK\n");
		return (0);
	}
	return (ft_printf("\033[0;31mKO\n"), 0);
}

int	main(int argc, char **argv)
{
	t_push_swap	p;

	p.arr = ++argv;
	if (argc == 2)
	{
		p.change_argv = 1;
		p.arr = ft_split(*argv, ' ');
		if (!p.arr)
			return (ft_printf("\033[0;33mError\n"), 1);
		while (p.arr[argc - 1])
			argc++;
		if (argc == 2)
		{
			if (p.change_argv)
				free_string_array(p.arr);
			return (ft_printf("\033[0;32mOK\n"));
		}
	}
	else
		p.change_argv = 0;
	if (argc == 1 || has_error_and_create_stack(&p) || operations(&p))
		return (0);
	if (p.change_argv)
		free_string_array(p.arr);
	return (ft_lstclear(&p.a, &del), ft_lstclear(&p.b, &del), 0);
}
