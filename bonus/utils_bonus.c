/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eates <eates@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 16:16:04 by eates             #+#    #+#             */
/*   Updated: 2025/12/31 13:34:38 by eates            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"
#include <unistd.h>

int	ft_isdigit(int c)
{
	return (c >= 48 && c <= 57);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	write_fill_char(int n, t_printf *pf)
{
	char	c;
	int		i;

	if (pf->has_zero)
		c = '0';
	else
		c = ' ';
	i = 0;
	while (i < n)
	{
		if (write_char(c, pf) == -1)
			return (-1);
		i++;
	}
	return (1);
}

char	*ft_strchr(const char *s, int c)
{
	size_t	i;
	char	a;

	a = c;
	i = -1;
	while (s[++i])
		if (s[i] == a)
			return ((char *)&s[i]);
	if (s[i] == a)
		return ((char *)&s[i]);
	return (NULL);
}

const char	*take_number_and_continue(const char *s, t_printf *pf)
{
	long	num;

	num = 0;
	while (ft_isdigit(*s))
	{
		num = num * 10 + (*s - '0');
		if (num > 2147483647)
			return (NULL);
		s++;
	}
	if (pf->has_dot)
		pf->decimal = num;
	else
		pf->width = num;
	return (s - 1);
}
