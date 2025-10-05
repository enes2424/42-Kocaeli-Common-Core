/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eates <eates@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 16:24:13 by eates             #+#    #+#             */
/*   Updated: 2023/07/04 17:36:46 by eates            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	strlen;
	char	*ret;

	if (!s)
		return (0);
	strlen = ft_strlen(s);
	if (strlen < start)
		return (ft_strdup(""));
	if (strlen - start < len)
		len = strlen - start;
	ret = malloc(len + 1);
	if (!ret)
		return (0);
	return (ft_strlcpy(ret, s + start, len + 1), ret);
}
