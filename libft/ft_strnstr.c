/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eates <eates@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 14:38:48 by eates             #+#    #+#             */
/*   Updated: 2023/07/04 14:56:23 by eates            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	c;
	size_t	needle_len;

	needle_len = ft_strlen(needle);
	if (needle_len == 0 || haystack == needle)
		return ((char *)haystack);
	i = -1;
	while (++i < len && haystack[i])
	{
		c = 0;
		while (i + c < len && haystack[i + c] && haystack[i + c] == needle[c])
			c++;
		if (c == needle_len)
			return ((char *)haystack + i);
	}
	return (NULL);
}
