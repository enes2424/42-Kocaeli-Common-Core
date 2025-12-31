/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_number.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eates <eates@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 12:16:20 by eates             #+#    #+#             */
/*   Updated: 2025/12/31 13:34:43 by eates            ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	write_int(int n, int *len)
{
	char	arr[10];
	int		i;

	i = 0;
	if (!n)
		return (write_char('0', len));
	if (n == -2147483648)
		return (write_string("-2147483648", len));
	if (n < 0)
	{
		if (write_char('-', len) == -1)
			return (-1);
		n = -n;
	}
	while (n)
	{
		arr[i++] = DECIMAL[n % 10];
		n /= 10;
	}
	while (i--)
		if (write_char(arr[i], len) == -1)
			return (-1);
	return (1);
}

int	write_uint(unsigned int n, int *len)
{
	int		arr[16];
	int		i;

	i = 0;
	if (!n)
		return (write_char('0', len));
	while (n)
	{
		arr[i++] = DECIMAL[n % 10];
		n /= 10;
	}
	while (i--)
		if (write_char(arr[i], len) == -1)
			return (-1);
	return (1);
}

int	write_hex(unsigned int n, char c, int *len)
{
	char	arr[16];
	int		i;
	char	*hex;

	i = 0;
	if (!n)
		arr[i++] = '0';
	if (c == 'x')
		hex = HEXALOW;
	else
		hex = HEXAUP;
	while (n)
	{
		arr[i++] = hex[n % 16];
		n /= 16;
	}
	while (i--)
		if (write_char(arr[i], len) == -1)
			return (-1);
	return (1);
}

int	write_point(void *ptr, int *len)
{
	char				arr[32];
	int					i;
	unsigned long long	nb;

	if (!ptr)
		return (write_string("(nil)", len));
	i = 0;
	nb = (unsigned long long)ptr;
	if (write_string("0x", len) == -1)
		return (-1);
	if (!nb)
		return (write_char('0', len));
	while (nb)
	{
		arr[i++] = HEXALOW[nb % 16];
		nb /= 16;
	}
	while (i--)
		if (write_char(arr[i], len) == -1)
			return (-1);
	return (1);
}
