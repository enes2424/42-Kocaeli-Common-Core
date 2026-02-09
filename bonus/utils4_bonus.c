/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eates <eates@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 05:36:09 by eates             #+#    #+#             */
/*   Updated: 2024/01/27 20:42:12 by eates            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include <math.h>
#include <stdlib.h>

void	raycasting(t_program *x, double i, int j)
{
	int			start;

	while (i >= 58.5 + x->angle)
	{
		x->is_door = 0;
		throwing_ray(x, i, tan(PI * i / 180.0));
		if (x->which_wall == 0)
			start = x->player.new_x % PIXEL;
		else if (x->which_wall == 1)
			start = x->player.new_y % PIXEL;
		else if (x->which_wall == 2)
			start = PIXEL - x->player.new_x % PIXEL - 1;
		else if (x->which_wall == 3)
			start = PIXEL - x->player.new_y % PIXEL - 1;
		x->player.new_x += (x->which_wall == 1) - (x->which_wall == 3);
		x->player.new_y += (x->which_wall == 2) - (x->which_wall == 0);
		x->tmp_img = (t_mlx_image *)(((size_t)x->mlx.door) * x->is_door
				+ ((size_t)x->mlx.walls[x->which_wall]) * !x->is_door);
		put_image(x, round(225000
				* fabs(1 / cos(PI * (i - x->angle - 90) / 180))
				/ sqrt(pow((x->player.new_x - x->player.x), 2)
					+ pow((x->player.new_y - x->player.y), 2))), j++, start);
		i -= 0.035;
	}
}

void	throwing_ray(t_program *x, double angle, double tanjant)
{
	double			different[2];
	int				a[2];

	x->px[0] = cos(PI * angle / 180.0);
	x->py[0] = sin(PI * angle / 180.0);
	x->which_wall = throwing_straight_ray(x, x->px[0], x->py[0], 0);
	if (x->which_wall + 1)
		return ;
	a[0] = x->px[0] > 0;
	a[1] = x->py[0] < 0;
	x->px[0] = (x->player.x / PIXEL + a[0]) * PIXEL - a[0];
	x->py[0] = x->player.y
		+ (x->player.x % PIXEL + a[0] * (1 - PIXEL)) * tanjant;
	x->py[1] = (x->player.y / PIXEL + a[1]) * PIXEL - a[1];
	x->px[1] = x->player.x
		+ (x->player.y % PIXEL + a[1] * (1 - PIXEL)) / tanjant;
	different[0] = (1 - 2 * a[0]) * PIXEL * tanjant;
	different[1] = (1 - 2 * a[1]) * PIXEL / tanjant;
	throwing_not_straight_ray(x, different, a);
}

int	throwing_straight_ray2(t_program *x, double px, double py, int tmp)
{
	char	c;

	if (py)
		return (-1);
	x->player.new_y = x->player.y;
	tmp = x->player.x / PIXEL;
	if (px < 0)
	{
		while (--tmp >= 0)
		{
			c = x->map.cropped_map[x->player.y / PIXEL][tmp];
			if (c == '1' || (c == 'D' && !search(x->doors,
						tmp, x->player.y / PIXEL)->is_open))
				return (x->is_door = (c == 'D'),
					x->player.new_x = (tmp + 1) * PIXEL, 3);
		}
	}
	while (1)
	{
		c = x->map.cropped_map[x->player.y / PIXEL][++tmp];
		if (c == '1' || (c == 'D' && !search(x->doors,
					tmp, x->player.y / PIXEL)->is_open))
			return (x->is_door = (c == 'D'),
				x->player.new_x = tmp * PIXEL - 1, 1);
	}
}

int	throwing_straight_ray(t_program *x, double px, double py, int tmp)
{
	char	c;

	if (px)
		return (throwing_straight_ray2(x, px, py, tmp));
	x->player.new_x = x->player.x;
	tmp = x->player.y / PIXEL;
	if (py > 0)
	{
		while (--tmp >= 0)
		{
			c = x->map.cropped_map[tmp][x->player.x / PIXEL];
			if (c == '1' || (c == 'D' && !search(x->doors,
						x->player.x / PIXEL, tmp)->is_open))
				return (x->is_door = (c == 'D'),
					x->player.new_y = (tmp + 1) * PIXEL, 0);
		}
	}
	while (1)
	{
		c = x->map.cropped_map[++tmp][x->player.x / PIXEL];
		if (c == '1' || (c == 'D' && !search(x->doors,
					x->player.x / PIXEL, tmp)->is_open))
			return (x->is_door = (c == 'D'),
				x->player.new_y = tmp * PIXEL - 1, 2);
	}
}

void	throwing_not_straight_ray(t_program *x, double *different, int *a)
{
	while (1)
	{
		if ((1 - 2 * a[1]) * x->py[0] > (1 - 2 * a[1]) * x->py[1])
		{
			if (throwing_ray1(x, different, a))
				return ;
			continue ;
		}
		if (throwing_ray2(x, different, a))
			return ;
	}
}
