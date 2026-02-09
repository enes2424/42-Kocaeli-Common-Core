/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eates <eates@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 15:13:59 by eates             #+#    #+#             */
/*   Updated: 2024/01/27 18:22:50 by eates            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

int	ft_putendl_fd(char *s, int fd)
{
	int	tmp;

	if (!s)
		return (0);
	tmp = write(fd, s, ft_strlen(s));
	if (tmp == -1)
		return (-1);
	if (write(fd, "\n", 1) == -1)
		return (-1);
	return (++tmp);
}
