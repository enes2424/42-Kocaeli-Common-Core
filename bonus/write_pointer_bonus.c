/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_pointer_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eates <eates@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 16:43:58 by eates             #+#    #+#             */
/*   Updated: 2025/12/31 13:34:38 by eates            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

static int	continue_write_pointer_with_flags(char arr[], int i, t_printf *pf)
{
	int	j;

	j = i + 2;
	if (!pf->has_minus && write_fill_char(pf->width - j, pf) == -1)
		return (-1);
	if (write_string("0x", pf) == -1)
		return (-1);
	while (i--)
		if (write_char(arr[i], pf) == -1)
			return (-1);
	if (pf->has_minus && write_fill_char(pf->width - j, pf) == -1)
		return (-1);
	return (1);
}

int	write_pointer_with_flags(void *ptr, t_printf *pf)
{
	unsigned long long	nb;
	char				arr[32];
	int					i;

	if (!ptr)
	{
		pf->unlimit = 1;
		return (write_string_with_flags("(nil)", pf));
	}
	i = 0;
	nb = (unsigned long long)ptr;
	if (!nb)
	{
		pf->unlimit = 1;
		return (write_string_with_flags("0x0", pf));
	}
	while (nb)
	{
		arr[i++] = HEXALOW[nb % 16];
		nb /= 16;
	}
	return (continue_write_pointer_with_flags(arr, i, pf));
}
