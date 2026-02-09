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

#include <sys/_types/_size_t.h>

char	*ft_strrchr(const char *s, int c)
{
	size_t		i;
	char		*ptr;
	char		a;

	i = 0;
	ptr = 0;
	a = c;
	while (s[i] != '\0')
	{
		if (s[i] == a)
			ptr = (char *)&s[i];
		i++;
	}
	if (s[i] == a)
		ptr = (char *)&s[i];
	return (ptr);
}
