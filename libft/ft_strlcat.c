/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eates <eates@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 10:24:13 by eates             #+#    #+#             */
/*   Updated: 2023/07/04 11:49:06 by eates            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	s;
	size_t	d;

	if (!dst && dstsize == 0)
		return (ft_strlen(src));
	d = ft_strlen(dst);
	if (dstsize <= d)
		return (dstsize + ft_strlen(src));
	s = 0;
	while (src[s] && d + 1 < dstsize)
		dst[d++] = src[s++];
	return (dst[d] = '\0', d - s + ft_strlen(src));
}
