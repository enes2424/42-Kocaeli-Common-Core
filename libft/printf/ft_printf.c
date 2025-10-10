/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eates <eates@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 12:16:43 by eates             #+#    #+#             */
/*   Updated: 2023/09/05 12:16:44 by eates            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	format(va_list *args, char c, int *len)
{
	if (c == 'c')
		return (writechar(va_arg(*args, int), len));
	if (c == 's')
		return (writestring(va_arg(*args, char *), len));
	if (c == 'd' || c == 'i')
		return (writeint(va_arg(*args, int), len));
	if (c == 'u')
		return (writeuint(va_arg(*args, unsigned int), len));
	if (c == 'p')
		return (writepoint(va_arg(*args, void *), len));
	if (c == 'x' || c == 'X')
		return (writehex(va_arg(*args, unsigned int), c, len));
	if (c == '%')
		return (writechar('%', len));
	return (-1);
}

int	ft_printf(const char *s, ...)
{
	va_list		args;
	int			len;

	if (LOCATION == 2 && !s)
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
		else if (writechar(*s, &len) == -1)
			return (va_end(args), -1);
		s++;
	}
	return (va_end(args), len);
}
