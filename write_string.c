/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eates <eates@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 12:18:20 by eates             #+#    #+#             */
/*   Updated: 2025/12/31 13:34:38 by eates            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <unistd.h>

int	write_char(char c, int *len)
{
	return ((*len)++, write(1, &c, 1));
}

int	write_string(char *s, int *len)
{
	if (!s)
		s = "(null)";
	while (*s)
		if (write_char(*s++, len) == -1)
			return (-1);
	return (1);
}
