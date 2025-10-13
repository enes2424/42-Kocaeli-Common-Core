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

#include <stddef.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	char	*tmp_s;
	size_t	i;
	char	a;

	tmp_s = (char *)s;
	a = c;
	i = -1;
	while (++i < n)
		if (tmp_s[i] == a)
			return ((void *)&s[i]);
	return (0);
}
