/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eates <eates@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 12:19:31 by eates             #+#    #+#             */
/*   Updated: 2023/07/05 15:19:39 by eates            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	const char		*tmp_s;
	char			a;

	i = 0;
	tmp_s = (char *)s;
	a = (char)c;
	while (i < n)
	{
		if (tmp_s[i] == a)
			return ((void *)&s[i]);
		i++;
	}
	return (0);
}
