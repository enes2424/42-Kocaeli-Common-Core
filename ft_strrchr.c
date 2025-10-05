/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eates <eates@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 12:19:31 by eates             #+#    #+#             */
/*   Updated: 2023/07/04 12:49:39 by eates            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;
	char	a;

	a = c;
	i = ft_strlen(s) + 1;
	while (i-- > 0)
		if (s[i] == a)
			return ((char *)&s[i]);
	return (NULL);
}
