/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eates <eates@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 16:34:59 by eates             #+#    #+#             */
/*   Updated: 2023/08/06 15:18:08 by eates            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "libft/libft.h"

typedef struct s_push_swap
{
	t_list	*a;
	t_list	*b;
	int		change_argv;
	char	**arr;
}	t_push_swap;

int		push(t_list **stack, int content);
int		pop(t_list **stack);
void	del(void *content);
int		get(t_list *stack, int index);
void	set(t_list *stack, int index, int new_content);
void	s(t_list *stack);
int		p(t_list **stack1, t_list **stack2);
void	r(t_list *stack);
void	rr(t_list *stack);
int		min(t_list *stack);
int		max(t_list *stack);
int		is_it_in_order(t_list *stack);
int		has_error_and_create_stack(t_push_swap	*p);
int		in_list(t_list *stack, int num);
void	function(t_list *a);
void	error(t_push_swap	*p);
void	p_operations(t_push_swap *pu, t_list **a, t_list **b, int x);
void	s_operations(t_push_swap *p, char c);
void	r_operations(t_push_swap *p, char c);
void	rr_operations(t_push_swap *p, char c);
void	basic_sort(t_push_swap	*p);
void	sort_three_arg(t_list **a);
int		ft_atoi(const char *str, t_push_swap *p, void (*del)(void*));
int		quicksort_a(t_push_swap *p, int len, int count);
int		quicksort_b(t_push_swap *p, int len, int count);
void	sort_array(int *sorted_array, int size);
int		is_sorted(t_list *stack, char c, int len);
int		get_middle(int *pivot, t_list *a, int size);

#endif
