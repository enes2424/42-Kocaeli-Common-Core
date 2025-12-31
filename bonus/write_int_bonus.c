/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_int_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eates <eates@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 12:16:20 by eates             #+#    #+#             */
/*   Updated: 2025/12/31 13:34:38 by eates            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

static int	continue_write_int_with_flags_4(char *arr, int i, \
	int j, t_printf *pf)
{
	if (!(pf->has_dot && pf->decimal == 0 && arr[i - 1] == '0'))
		while (i--)
			if (write_char(arr[i], pf) == -1)
				return (-1);
	if (pf->has_minus && write_fill_char(pf->width - j, pf) == -1)
		return (-1);
	return (1);
}

static int	continue_write_int_with_flags_3(char *arr, \
	int is_negative, int **ijarr, t_printf *pf)
{
	int	i;
	int	j;

	i = *ijarr[0];
	j = *ijarr[1];
	if (pf->has_dot)
	{
		pf->has_zero = 1;
		if (is_negative)
		{
			if (write_char('-', pf) == -1)
				return (-1);
			i--;
		}
		else if (pf->has_plus)
		{
			if (write_char('+', pf) == -1)
				return (-1);
			i--;
		}
		if (write_fill_char(pf->decimal - i, pf) == -1)
			return (-1);
		pf->has_zero = 0;
	}
	return (continue_write_int_with_flags_4(arr, i, j, pf));
}

static int	continue_write_int_with_flags_2(char *arr, \
	int is_negative, int **ijarr, t_printf *pf)
{
	int	*i;
	int	*j;

	i = ijarr[0];
	j = ijarr[1];
	if (pf->has_space && !is_negative && (pf->width - *j <= 0 || \
		pf->has_minus || pf->has_zero))
	{
		if (write_char(' ', pf) == -1)
			return (-1);
		if (pf->has_minus || pf->has_zero)
			(*j)++;
	}
	if (pf->has_dot && pf->decimal == 0 && arr[*i - 1] == '0')
		(*j)--;
	if (!pf->has_minus && write_fill_char(pf->width - *j, pf) == -1)
		return (-1);
	return (continue_write_int_with_flags_3(arr, is_negative, ijarr, pf));
}

static int	continue_write_int_with_flags_1(char *arr, int is_negative, \
	int i, t_printf *pf)
{
	int	j;
	int	*ijarr[2];

	j = i;
	if (pf->has_dot && pf->decimal > j)
		j = pf->decimal;
	if (is_negative)
	{
		if (!pf->has_zero)
			arr[i++] = '-';
		else if (write_char('-', pf) == -1)
			return (-1);
		j++;
	}
	else if (pf->has_plus)
	{
		if (!pf->has_zero)
			arr[i++] = '+';
		else if (write_char('+', pf) == -1)
			return (-1);
		j++;
	}
	ijarr[0] = &i;
	ijarr[1] = &j;
	return (continue_write_int_with_flags_2(arr, is_negative, ijarr, pf));
}

int	write_int_with_flags(int n, t_printf *pf)
{
	char	arr[11];
	int		is_negative;
	int		i;

	i = 0;
	if (n == -2147483648)
	{
		pf->unlimit = 1;
		return (write_string_with_flags("-2147483648", pf));
	}
	is_negative = n < 0;
	if (is_negative)
		n = -n;
	if (!n)
		arr[i++] = '0';
	while (n)
	{
		arr[i++] = DECIMAL[n % 10];
		n /= 10;
	}
	return (continue_write_int_with_flags_1(arr, is_negative, i, pf));
}
