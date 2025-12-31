/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_string_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eates <eates@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 12:18:20 by eates             #+#    #+#             */
/*   Updated: 2025/12/31 13:34:38 by eates            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"
#include <unistd.h>

int	write_string(char *s, t_printf *pf)
{
	int	limit;
	int	i;

	if (pf->has_dot && !pf->unlimit)
		limit = pf->decimal;
	else
		limit = 2147483647;
	i = 0;
	while (*s && i < limit)
	{
		if (write_char(*s++, pf) == -1)
			return (-1);
		i++;
	}
	return (1);
}

int	write_string_with_flags(char *s, t_printf *pf)
{
	int	len;

	if (!s)
	{
		if (pf->has_dot && pf->decimal < 6)
			s = "";
		else
			s = "(null)";
	}
	len = ft_strlen(s);
	if (pf->has_dot && !pf->unlimit && len > pf->decimal)
		len = pf->decimal;
	if (!pf->has_minus && write_fill_char(pf->width - len, pf) == -1)
		return (-1);
	if (write_string(s, pf) == -1)
		return (-1);
	if (pf->has_minus && write_fill_char(pf->width - len, pf) == -1)
		return (-1);
	return (1);
}
