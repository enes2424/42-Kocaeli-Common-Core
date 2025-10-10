/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eates <eates@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 13:41:34 by eates             #+#    #+#             */
/*   Updated: 2023/07/05 14:29:00 by eates            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_itoa(int n)
{
	char	*num;
	int		len;
	int		tmp;
	int		sign;

	len = ((tmp = n) <= 0) - 1;
	while (len++, tmp != 0)
		tmp /= 10;
	num = malloc(len + 1);
	if (!num)
		return (NULL);
	num[len--] = '\0';
	num[0] = '0' - 3 * ((sign = -2 * (n < 0) + 1) == -1);
	while (n != 0)
	{
		num[len--] = sign * (n % 10) + '0';
		n /= 10;
	}
	return (num);
}
