/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eates <eates@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 12:16:43 by eates             #+#    #+#             */
/*   Updated: 2025/12/31 13:34:38 by eates            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	format(va_list *args, char c, int *len)
{
	if (c == 'c')
		return (write_char(va_arg(*args, int), len));
	if (c == 's')
		return (write_string(va_arg(*args, char *), len));
	if (c == 'd' || c == 'i')
		return (write_int(va_arg(*args, int), len));
	if (c == 'u')
		return (write_uint(va_arg(*args, unsigned int), len));
	if (c == 'p')
		return (write_point(va_arg(*args, void *), len));
	if (c == 'x' || c == 'X')
		return (write_hex(va_arg(*args, unsigned int), c, len));
	if (c == '%')
		return (write_char('%', len));
	return (-1);
}

int	ft_printf(const char *s, ...)
{
	va_list		args;
	int			len;

	if (!s)
		return (-1);
	len = 0;
	va_start(args, s);
	while (*s)
	{
		if (*s == '%')
		{
			if (format(&args, *++s, &len) == -1)
				return (va_end(args), -1);
		}
		else if (write_char(*s, &len) == -1)
			return (va_end(args), -1);
		s++;
	}
	return (va_end(args), len);
}
