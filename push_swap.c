/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eates <eates@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 10:09:01 by eates             #+#    #+#             */
/*   Updated: 2023/08/07 13:25:32 by eates            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdlib.h>

static void	operations(t_push_swap	*p, int argc)
{
	if (has_error_and_create_stack(p))
		exit(1);
	if (argc == 4)
		sort_three_arg(&(p->a));
	else if (argc < 11)
		basic_sort(p);
	else
		quicksort_a(p, ft_lstsize(p->a), 0);
}

int	main(int argc, char **argv)
{
	t_push_swap	p;

	argv++;
	p.arr = argv;
	p.change_argv = 0;
	if (argc == 2)
	{
		p.change_argv = 1;
		p.arr = ft_split(*argv, ' ');
		if (!p.arr)
			return (ft_printf("\033[0;33mError\n"), 1);
		while (p.arr[argc - 1])
			argc++;
	}
	operations(&p, argc);
	if (p.change_argv)
		free_string_array(p.arr);
	return (ft_lstclear(&p.a, &del), 0);
}
