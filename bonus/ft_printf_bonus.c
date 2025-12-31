/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eates <eates@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 12:16:43 by eates             #+#    #+#             */
/*   Updated: 2025/12/31 13:34:38 by eates            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"
#include <unistd.h>

static int	format(va_list *args, char c, t_printf *pf)
{
	if (pf->width == -1)
		pf->width = 0;
	if (c == 'c')
		return (write_char_with_flags(va_arg(*args, int), pf));
	if (c == 's')
		return (write_string_with_flags(va_arg(*args, char *), pf));
	if (c == 'p')
		return (write_pointer_with_flags(va_arg(*args, void *), pf));
	if (c == 'd' || c == 'i')
		return (write_int_with_flags(va_arg(*args, int), pf));
	if (c == 'u')
		return (write_uint_with_flags(va_arg(*args, unsigned int), pf));
	if (c == 'x' || c == 'X')
		return (write_hex_with_flags(va_arg(*args, unsigned int), c, pf));
	if (c == '%')
		return (write_char('%', pf));
	return (-1);
}

static const char	*parse_format(va_list *args, const char *s, t_printf *pf)
{
	while (ft_strchr("csdiupxX%", *s) == NULL)
	{
		if (*s == '-')
			pf->has_minus = 1;
		else if (*s == '#')
			pf->has_sharp = 1;
		else if (*s == ' ')
			pf->has_space = 1;
		else if (*s == '+')
			pf->has_plus = 1;
		else if (*s == '.')
			pf->has_dot = 1 + (pf->has_zero = 0);
		else if (ft_isdigit(*s))
		{
			if (*s == '0' && !pf->has_dot)
				pf->has_zero = 1;
			s = take_number_and_continue(s, pf);
			if (s == NULL)
				return (NULL);
		}
		s++;
	}
	if (format(args, *s, pf) == -1)
		return (NULL);
	return (s);
}

static void	reset_flags(t_printf *pf)
{
	pf->has_minus = 0;
	pf->has_dot = 0;
	pf->has_sharp = 0;
	pf->has_space = 0;
	pf->has_plus = 0;
	pf->decimal = 0;
	pf->width = -1;
	pf->has_zero = 0;
	pf->unlimit = 0;
}

int	ft_printf(const char *s, ...)
{
	va_list		args;
	t_printf	pf;

	if (!s)
		return (-1);
	pf.len = 0;
	va_start(args, s);
	while (*s)
	{
		if (*s == '%')
		{
			reset_flags(&pf);
			s = parse_format(&args, ++s, &pf);
			if (s == NULL)
				return (va_end(args), -1);
		}
		else if (write_char(*s, &pf) == -1)
			return (va_end(args), -1);
		s++;
	}
	return (va_end(args), pf.len);
}
