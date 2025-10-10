/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eates <eates@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 15:01:07 by eates             #+#    #+#             */
/*   Updated: 2023/07/20 17:06:28 by eates            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdlib.h>

int	ft_atoi(const char *str, t_push_swap *p, void (*del)(void*))
{
	long	i;
	long	num;
	int		sign;

	i = 0;
	num = 0;
	sign = 1;
	while (str[i] != '\0' && (str[i] == 32 || str[i] == '\t' || str[i] == '\n'
			|| str[i] == '\r' || str[i] == '\v' || str[i] == '\f'))
		i++;
	if (str[i] && (str[i] == '-' || str[i] == '+'))
		if (str[i++] == '-')
			sign = -1;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
		num = (num * 10) + (str[i++] - '0');
	if (num > 2147483647L + (sign - 1) / -2
		|| (num == 0 && !str[i] && str[i - 1] != '0'))
	{
		if (p->change_argv)
			free_string_array(p->arr);
		ft_putendl_fd("Error", 1);
		return (ft_lstclear(&(p->a), del), exit(1), 0);
	}
	return (sign * num);
}
