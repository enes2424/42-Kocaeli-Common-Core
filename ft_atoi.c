/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eates <eates@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 15:01:07 by eates             #+#    #+#             */
/*   Updated: 2023/07/04 15:27:41 by eates            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

int	ft_atoi(const char *str)
{
	size_t	i;
	int		num;
	int		sign;

	i = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	sign = -2 * (str[i] == '-') + 1;
	i += (sign == -1 || str[i] == '+');
	num = 0;
	while (str[i] >= 48 && str[i] <= 57)
		num = num * 10 + sign * (str[i++] - 48);
	return (num);
}
