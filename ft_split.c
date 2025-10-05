/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eates <eates@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 11:31:06 by eates             #+#    #+#             */
/*   Updated: 2023/07/11 13:52:47 by eates            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_words(char const *s, char c)
{
	size_t	num_of_words;

	num_of_words = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (!*s)
			break ;
		num_of_words++;
		while (*s && *s != c)
			s++;
	}
	return (num_of_words);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	size_t	len;
	size_t	i;

	if (!s)
		return (NULL);
	len = count_words(s, c);
	tab = malloc(sizeof(char *) * (len + 1));
	if (!tab)
		return (NULL);
	i = -1;
	while (++i < len)
	{
		while (*s == c)
			s++;
		tab[i] = ft_substr(s, 0, ft_strchr(s, c) - s);
		if (!tab[i])
		{
			while (i-- > 0)
				free(tab[i]);
			return (free(tab), NULL);
		}
		s += ft_strlen(tab[i]);
	}
	return (tab[i] = NULL, tab);
}
