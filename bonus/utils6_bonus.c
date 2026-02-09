/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils6_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eates <eates@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 05:36:02 by eates             #+#    #+#             */
/*   Updated: 2024/01/27 18:35:45 by eates            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include "../minilibx/mlx.h"
#include "../libft/libft.h"

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

void	render_continue(t_program *x, int mx, int my, int i)
{
	int	j;
	int	state1;
	int	state2;

	state1 = i + 13;
	state2 = mx / PIXEL2 + 12;
	while (++i <= state1 && x->map.cropped_map[i])
	{
		j = mx / PIXEL2 - 1;
		while (++j <= state2 && x->map.cropped_map[i][j])
		{
			if (x->map.cropped_map[i][j] == '1')
				mlx_put_image_to_window(x->mlx.ptr, x->mlx.win,
					x->mlx.wall, j * PIXEL2 - mx, i * PIXEL2 - my);
			else if (x->map.cropped_map[i][j] == 'D')
				mlx_put_image_to_window(x->mlx.ptr, x->mlx.win,
					x->mlx.mdoor, j * PIXEL2 - mx, i * PIXEL2 - my);
			else if (x->map.cropped_map[i][j] != ' ')
				mlx_put_image_to_window(x->mlx.ptr, x->mlx.win,
					x->mlx.floor, j * PIXEL2 - mx, i * PIXEL2 - my);
		}
	}
	render_continue_continue(x, mx, my);
}

void	render_continue_continue(t_program *x, int mx, int my)
{
	mlx_put_image_to_window(x->mlx.ptr, x->mlx.win, x->mlx.player,
		x->player.x / PIXEL * PIXEL2 - mx, x->player.y / PIXEL * PIXEL2 - my);
	mlx_pixel_put(x->mlx.ptr, x->mlx.win, x->player.x * PIXEL2 / PIXEL - mx,
		x->player.y * PIXEL2 / PIXEL - my, 0);
	x->tmp = ft_itoa(x->speed * x->multipler);
	check_malloc(x, x->tmp);
	x->tmp = ft_strjoin(x->tmp, " pixel / step");
	check_malloc(x, x->tmp);
	mlx_string_put(x->mlx.ptr, x->mlx.win, 1650, 30, 0, x->tmp);
	special_free((void **)&x->tmp);
}

int	exit_x(t_program *x)
{
	free_program(NULL, x, 0);
	return (0);
}

void	open_door(t_program *x)
{
	t_door	*door;

	if (x->map.cropped_map[x->player.y / PIXEL - 1][x->player.x / PIXEL] == 'D')
	{
		door = search(x->doors, x->player.x / PIXEL, x->player.y / PIXEL - 1);
		door->is_open = !door->is_open;
	}
	if (x->map.cropped_map[x->player.y / PIXEL + 1][x->player.x / PIXEL] == 'D')
	{
		door = search(x->doors, x->player.x / PIXEL, x->player.y / PIXEL + 1);
		door->is_open = !door->is_open;
	}
	if (x->map.cropped_map[x->player.y / PIXEL][x->player.x / PIXEL - 1] == 'D')
	{
		door = search(x->doors, x->player.x / PIXEL - 1, x->player.y / PIXEL);
		door->is_open = !door->is_open;
	}
	if (x->map.cropped_map[x->player.y / PIXEL][x->player.x / PIXEL + 1] == 'D')
	{
		door = search(x->doors, x->player.x / PIXEL + 1, x->player.y / PIXEL);
		door->is_open = !door->is_open;
	}
}
