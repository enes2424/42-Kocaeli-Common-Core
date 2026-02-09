/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils6.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eates <eates@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 05:36:02 by eates             #+#    #+#             */
/*   Updated: 2024/01/27 18:27:08 by eates            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdlib.h>

void	put_image2(t_program *x, int size, int j, int start)
{
	t_linkedlist	*list;
	int				i;
	int				z;
	int				k;

	list = x->list;
	exe(x, PIXEL - size % PIXEL, size / PIXEL, size % PIXEL);
	z = (size > 1000) * (size / 2 - 500);
	i = (size > 1000) * z * PIXEL / size - 1;
	while (++i < PIXEL)
	{
		k = -1;
		while (++k < list->data)
		{
			if (z + 500 - size / 2 > 1000)
				return ;
			*((unsigned int *)(x->mlx.screen->addr + (z + 500 - size / 2)
						* x->mlx.screen->size_line + j * 4))
				= *((unsigned int *)(x->tmp_img->addr
						+ i * 4 * PIXEL + start * 4));
			z++;
		}
		list = list->next;
	}
}

int	exit_x(t_program *x)
{
	free_program(NULL, x, 0);
	return (0);
}

int	handle(int key, t_program *x)
{
	if (key == ESC)
		return (free_program(NULL, x, 1), 1);
	if (key == W)
		x->player.keys[0] = 1;
	else if (key == S)
		x->player.keys[1] = 1;
	else if (key == A)
		x->player.keys[2] = 1;
	else if (key == D)
		x->player.keys[3] = 1;
	else if (key == L)
		x->player.keys[4] = 1;
	else if (key == R)
		x->player.keys[5] = 1;
	else if (key == UP)
		x->speed += (x->speed < 500) * 5;
	else if (key == DOWN)
		x->speed = (x->speed - 5) * (x->speed >= 5);
	else if (key == SHIFT)
		x->multipler = 2;
	else
		return (0);
	return (handle2(x));
}
