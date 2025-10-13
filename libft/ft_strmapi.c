/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eates <eates@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 14:33:43 by eates             #+#    #+#             */
/*   Updated: 2023/07/05 14:58:15 by eates            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	i;
	char	*string;

	if (!s || !f)
		return (NULL);
	string = malloc(ft_strlen(s) + 1);
	if (!string)
		return (NULL);
	i = -1;
	while (s[++i])
		string[i] = f(i, s[i]);
	return (string[i] = '\0', string);
}
