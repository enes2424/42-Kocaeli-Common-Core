/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eates <eates@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 12:19:31 by eates             #+#    #+#             */
/*   Updated: 2023/07/04 14:00:18 by eates            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

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
