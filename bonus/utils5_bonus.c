/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eates <eates@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 05:36:06 by eates             #+#    #+#             */
/*   Updated: 2024/01/27 19:45:10 by eates            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include "../libft/libft.h"

int	throwing_ray2(t_program *x, double *different, int *a)
{
	char	c;

	c = x->map.cropped_map[(int)((x->py[1] + 2 * a[1] - 1) / PIXEL)]
	[(int)(x->px[1] / PIXEL)];
	if (c == '1' || (c == 'D' && !search(x->doors, (int)(x->px[1] / PIXEL), \
			(int)((x->py[1] + 2 * a[1] - 1) / PIXEL))->is_open))
		return (x->is_door = (c == 'D'), x->which_wall = 2 * a[1],
			x->player.new_x = x->px[1], x->player.new_y = x->py[1], 1);
	c = x->map.cropped_map[(int)((x->py[1] + 2 * a[1] - 1) / PIXEL)]
	[(int)((x->px[1] + 2 * a[0] - 1) / PIXEL)];
	if (c == '1' || (c == 'D' && !search(x->doors, (int)((x->px[1] + 2 \
	* a[0] - 1) / PIXEL), (int)((x->py[1] + 2 * a[1] - 1) / PIXEL))->is_open))
	{
		x->is_door = (c == 'D');
		c = x->map.cropped_map[(int)(x->py[1] / PIXEL)]
		[(int)((x->px[1] + 2 * a[0] - 1) / PIXEL)];
		if ((!a[0] && !a[1]) || c == '1' || (c == 'D' && !search(x->doors,
					(int)((x->px[1] + 2 * a[0] - 1) / PIXEL),
				(int)(x->py[1] / PIXEL))->is_open))
			return (x->is_door = (c == 'D'), x->which_wall = 3,
				x->player.new_x = x->px[1], x->player.new_y = x->py[1], 1);
		return (x->which_wall = 2 * a[1], x->player.new_x = x->px[1],
			x->player.new_y = x->py[1], 1);
	}
	return (x->px[1] += different[1], x->py[1] += (2 * a[1] - 1) * PIXEL, 0);
}

void	put_image(t_program *x, int size, int j, int start)
{
	t_linkedlist	*list;
	int				i;
	int				k;

	list = x->list;
	if (size <= PIXEL)
	{
		exe(x, size - PIXEL % size, PIXEL / size, PIXEL % size);
		i = 0;
		k = -1;
		while (++k < size)
		{
			*((unsigned int *)(x->mlx.screen->addr + (k + 500 - size / 2)
						* x->mlx.screen->size_line + j * 4))
				= *((unsigned int *)(x->tmp_img->addr
						+ i * 4 * PIXEL + start * 4));
			i += list->data;
			list = list->next;
		}
		return ;
	}
	put_image2(x, size, j, start);
}

int	exe(t_program *x, int a, int b, int c)
{
	t_linkedlist	*list;
	int				arr[8];

	arr[3] = b + 1;
	list = x->list;
	if (c < a)
	{
		ft_swap(&a, &c);
		ft_swap(&b, &arr[3]);
	}
	else if (c == a)
	{
		arr[6] = -1;
		while (++arr[6] < a + c)
			list = add_node(x, list, (arr[6] % 2) * b + !(arr[6] % 2) * arr[3]);
		return (a + c);
	}
	arr[0] = a;
	arr[1] = b;
	arr[2] = c;
	arr[4] = c / (a + 1);
	arr[5] = (c - (a + 1) * arr[4]) / 2;
	arr[6] = -1;
	arr[7] = 0;
	return (exe2(x, list, arr));
}

t_linkedlist	*add_node(t_program *x, t_linkedlist *list, int value)
{
	list->data = value;
	if (!list->next)
		list->next = ft_calloc(1, sizeof(t_linkedlist));
	return (check_malloc(x, list->next), list->next);
}

int	exe2(t_program *x, t_linkedlist *list, int *arr)
{
	while (++arr[6] < arr[5])
		list = add_node(x, list, arr[3]);
	while (arr[6] < arr[0] + arr[2] - arr[4])
	{
		if ((arr[6] - arr[5] + 1) % (arr[4] + 1))
			list = add_node(x, list, arr[3]);
		else
		{
			if (arr[7] == arr[0])
				break ;
			list = add_node(x, list, arr[1]);
			arr[7]++;
		}
		arr[6]++;
	}
	while (++arr[6] <= arr[0] + arr[2])
		list = add_node(x, list, arr[3]);
	return (arr[0] + arr[2]);
}
