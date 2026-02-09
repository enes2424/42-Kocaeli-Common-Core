/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eates <eates@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 15:29:55 by eates             #+#    #+#             */
/*   Updated: 2023/07/08 11:14:48 by eates            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	*ft_calloc(size_t count, size_t size)
{
	unsigned int	s;
	char			*ptr;

	s = count * size;
	ptr = malloc(s * sizeof(char));
	if (!ptr)
		return (0);
	ft_bzero(ptr, s);
	return (ptr);
}
