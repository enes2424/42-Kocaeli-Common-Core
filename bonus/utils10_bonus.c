/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils10_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eates <eates@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 17:53:38 by eates             #+#    #+#             */
/*   Updated: 2024/01/29 12:55:52 by eates            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include "../minilibx/mlx.h"
#include "../libft/libft.h"

void	render(t_program *x)
{
	int	i;
	int	mx;
	int	my;

	mlx_clear_window(x->mlx.ptr, x->mlx.win);
	mlx_put_background(x);
	raycasting(x, 121.5 + x->angle, 0);
	mlx_put_image_to_window(x->mlx.ptr, x->mlx.win, x->mlx.screen->img, 0, 0);
	i = (x->player.y / PIXEL > 6) * (x->player.y / PIXEL - 6) - 1;
	my = (i + 1) * PIXEL2;
	mx = ((x->player.x / PIXEL > 6) * (x->player.x / PIXEL - 6)) * PIXEL2;
	render_continue(x, mx, my, i);
}

void	mlx_put_background(t_program *x)
{
	int	i;
	int	j;

	i = -1;
	while (++i < 1000)
	{
		j = -1;
		while (++j < 1800)
			*(unsigned int *)(x->mlx.screen->addr + i * x->mlx.screen->size_line
					+ 4 * j)
				= (i < 500) * x->colors.c_rpg + (i >= 500) * x->colors.f_rpg;
	}
}

int	throwing_ray1(t_program *x, double *different, int *a)
{
	char	c;

	c = x->map.cropped_map[(int)(x->py[0] / PIXEL)]
	[(int)((x->px[0] + 2 * a[0] - 1) / PIXEL)];
	if (c == '1' || (c == 'D' && !search(x->doors, (int)((x->px[0] \
		+ 2 * a[0] - 1) / PIXEL), (int)(x->py[0] / PIXEL))->is_open))
		return (x->is_door = (c == 'D'), x->which_wall = 3 - 2 * a[0],
			x->player.new_x = x->px[0], x->player.new_y = x->py[0], 1);
	c = x->map.cropped_map[(int)((x->py[0] + 2 * a[1] - 1) / PIXEL)]
	[(int)((x->px[0] + 2 * a[0] - 1) / PIXEL)];
	if (c == '1' || (c == 'D' && !search(x->doors, (int)((x->px[0] + 2 * \
	a[0] - 1) / PIXEL), (int)((x->py[0] + 2 * a[1] - 1) / PIXEL))->is_open))
	{
		x->is_door = (c == 'D');
		c = x->map.cropped_map \
	[(int)((x->py[0] + 2 * a[1] - 1) / PIXEL)][(int)(x->px[0] / PIXEL)];
		if (c == '1' || (c == 'D'
				&& !search(x->doors, (int)(x->px[0] / PIXEL),
				(int)((x->py[0] + 2 * a[1] - 1) / PIXEL))->is_open))
			return (x->is_door = (c == 'D'), x->which_wall = 0,
				x->player.new_x = x->px[0], x->player.new_y = x->py[0], 1);
		return (x->which_wall = 3 - 2 * a[0], x->player.new_x = x->px[0],
			x->player.new_y = x->py[0], 1);
	}
	return (x->py[0] += different[0], x->px[0] += (2 * a[0] - 1) * PIXEL, 0);
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
	else if (key == SPACE)
		open_door(x);
	else
		return (0);
	return (handle2(x));
}

char	*control(t_program *x)
{
	char	*tmp;
	int		i;

	if (!ft_strstr(x->tmp, "NO ") || !ft_strstr(x->tmp, "SO ")
		|| !ft_strstr(x->tmp, "WE ") || !ft_strstr(x->tmp, "EA ")
		|| !ft_strstr(x->tmp, "F ") || !ft_strstr(x->tmp, "C ")
		|| !ft_strstr(x->tmp, "D "))
		return (free_program("The map contains incomplete information!!!"
				, x, 1), NULL);
	tmp = x->tmp;
	i = -1;
	while (++i < 7)
		tmp = control2(x, tmp);
	while (ft_isspaces(*tmp))
	{
		if (*tmp == '\n' && tmp++)
			continue ;
		i = 1;
		while (tmp[i] && ft_isspaces(tmp[i]) && tmp[i] != '\n')
			i++;
		if (tmp[i] != '\n')
			break ;
		tmp += i + 1;
	}
	return (tmp = ft_strdup(tmp), free(x->tmp), x->tmp = tmp);
}
