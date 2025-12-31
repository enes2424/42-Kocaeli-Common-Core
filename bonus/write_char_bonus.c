/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_char_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eates <eates@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 12:18:20 by eates             #+#    #+#             */
/*   Updated: 2025/12/31 13:34:38 by eates            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"
#include <unistd.h>

int	write_char(char c, t_printf *pf)
{
	return (pf->len++, write(1, &c, 1));
}

int	write_char_with_flags(char c, t_printf *pf)
{
	if (!pf->has_minus && write_fill_char(pf->width - 1, pf) == -1)
		return (-1);
	if (write_char(c, pf) == -1)
		return (-1);
	if (pf->has_minus && write_fill_char(pf->width - 1, pf) == -1)
		return (-1);
	return (1);
}
