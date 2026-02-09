/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eates <eates@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 17:44:35 by eates             #+#    #+#             */
/*   Updated: 2023/12/16 10:50:57 by eates            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strdup(const char *s1)
{
	char	*dest;
	int		size;

	size = ft_strlen(s1) + 1;
	dest = (char *) malloc(sizeof(char) * size);
	if (!dest)
		return (0);
	dest = ft_memmove(dest, s1, size);
	return (dest);
}
