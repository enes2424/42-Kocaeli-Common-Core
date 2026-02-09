/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eates <eates@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 15:13:59 by eates             #+#    #+#             */
/*   Updated: 2023/07/15 17:07:21 by eates            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

int	ft_putendl_fd(char *s, int fd)
{
	int	tmp;

	tmp = write(fd, s, ft_strlen(s));
	if (tmp == -1)
		return (-1);
	if (write(fd, "\n", 1) == -1)
		return (-1);
	return (++tmp);
}
