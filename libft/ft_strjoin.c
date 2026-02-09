/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eates <eates@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 17:40:00 by eates             #+#    #+#             */
/*   Updated: 2024/01/22 14:16:44 by eates            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*res;
	size_t	i;
	size_t	j;

	if (!s2)
		return (free(s1), NULL);
	if (!s1)
		return (ft_strdup(s2));
	res = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!res)
		return (free(s1), NULL);
	i = -1;
	j = -1;
	while (s1 && s2 && res && s1[++i] != '\0')
		res[i] = s1[i];
	while (s1 && s2 && res && (++j == 0 || s2[j - 1] != '\0'))
		res[i++] = s2[j];
	return (free(s1), res);
}
