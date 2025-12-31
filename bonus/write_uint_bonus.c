/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_uint_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eates <eates@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 15:58:48 by eates             #+#    #+#             */
/*   Updated: 2025/12/31 13:34:38 by eates            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

static int	continue_write_uint_with_flags(int *arr, int i, t_printf *pf)
{
	int	j;

	j = i;
	if (pf->has_dot && pf->decimal > j)
		j = pf->decimal;
	if (pf->has_dot && pf->decimal == 0 && arr[i - 1] == '0')
		j--;
	if (!pf->has_minus && write_fill_char(pf->width - j, pf) == -1)
		return (-1);
	if (pf->has_dot)
	{
		pf->has_zero = 1;
		if (write_fill_char(pf->decimal - i, pf) == -1)
			return (-1);
		pf->has_zero = 0;
	}
	if (!(pf->has_dot && pf->decimal == 0 && arr[i - 1] == '0'))
		while (i--)
			if (write_char(arr[i], pf) == -1)
				return (-1);
	if (pf->has_minus && write_fill_char(pf->width - j, pf) == -1)
		return (-1);
	return (1);
}

int	write_uint_with_flags(unsigned int n, t_printf *pf)
{
	int		arr[16];
	int		i;

	i = 0;
	if (!n)
		arr[i++] = '0';
	while (n)
	{
		arr[i++] = DECIMAL[n % 10];
		n /= 10;
	}
	return (continue_write_uint_with_flags(arr, i, pf));
}
