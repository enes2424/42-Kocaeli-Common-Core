/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   writestring.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eates <eates@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 12:18:20 by eates             #+#    #+#             */
/*   Updated: 2023/09/05 12:18:31 by eates            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <unistd.h>

int	writechar(char c, int *len)
{
	return ((*len)++, write(1, &c, 1));
}

int	writestring(char *s, int *len)
{
	if (!s)
		s = "(null)";
	while (*s)
		if (writechar(*s++, len) == -1)
			return (-1);
	return (1);
}
