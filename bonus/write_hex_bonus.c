/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_hex_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eates <eates@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 16:01:29 by eates             #+#    #+#             */
/*   Updated: 2025/12/31 13:34:38 by eates            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

static int	continue_write_hex_with_flags_2(char *arr, \
	int i, int j, t_printf *pf)
{
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

static int	continue_write_hex_with_flags(char *arr, char c, \
	int i, t_printf *pf)
{
	int	j;

	j = i;
	if (pf->has_dot && pf->decimal > j)
		j = pf->decimal;
	if (pf->has_sharp && arr[i - 1] != '0')
		j += 2;
	if (pf->has_dot && pf->decimal == 0 && arr[i - 1] == '0')
		j--;
	if (!(pf->has_sharp && arr[i - 1] != '0' && pf->has_zero))
		if (!pf->has_minus && write_fill_char(pf->width - j, pf) == -1)
			return (-1);
	if (pf->has_sharp && arr[i - 1] != '0')
	{
		if (write_char('0', pf) == -1)
			return (-1);
		if (write_char(c, pf) == -1)
			return (-1);
		if (pf->has_zero && !pf->has_minus && \
			write_fill_char(pf->width - j, pf) == -1)
			return (-1);
	}
	return (continue_write_hex_with_flags_2(arr, i, j, pf));
}

int	write_hex_with_flags(unsigned int n, char c, t_printf *pf)
{
	char	arr[16];
	char	*hex;
	int		i;

	i = 0;
	if (c == 'x')
		hex = HEXALOW;
	else
		hex = HEXAUP;
	if (!n)
		arr[i++] = '0';
	while (n)
	{
		arr[i++] = hex[n % 16];
		n /= 16;
	}
	return (continue_write_hex_with_flags(arr, c, i, pf));
}
