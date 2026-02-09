/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eates <eates@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 05:36:09 by eates             #+#    #+#             */
/*   Updated: 2024/01/29 14:15:03 by eates            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

void	raycasting(t_program *x, double i, int j)
{
	int			start;

	while (i >= 58.5 + x->angle)
	{
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
		x->tmp_img = x->mlx.walls[x->which_wall];
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
	different[0] = (1 - 2 * a[0]) * PIXEL * tanjant;
	x->py[1] = (x->player.y / PIXEL + a[1]) * PIXEL - a[1];
	x->px[1] = x->player.x
		+ (x->player.y % PIXEL + a[1] * (1 - PIXEL)) / tanjant;
	different[1] = (1 - 2 * a[1]) * PIXEL / tanjant;
	throwing_not_straight_ray(x, different, a);
}

int	throwing_straight_ray(t_program *x, double px, double py, int tmp)
{
	if (px == 0)
	{
		x->player.new_x = x->player.x;
		tmp = x->player.y / PIXEL;
		if (py > 0)
			while (--tmp >= 0)
				if (x->map.map[tmp][x->player.x / PIXEL] == '1')
					return (x->player.new_y = (tmp + 1) * PIXEL, 0);
		while (++tmp)
			if (x->map.map[tmp][x->player.x / PIXEL] == '1')
				return (x->player.new_y = tmp * PIXEL - 1, 2);
	}
	if (py == 0)
	{
		x->player.new_y = x->player.y;
		tmp = x->player.x / PIXEL;
		if (px < 0)
			while (--tmp >= 0)
				if (x->map.map[x->player.y / PIXEL][tmp] == '1')
					return (x->player.new_x = (tmp + 1) * PIXEL, 3);
		while (++tmp)
			if (x->map.map[x->player.y / PIXEL][tmp] == '1')
				return (x->player.new_x = tmp * PIXEL - 1, 1);
	}
	return (-1);
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

int	throwing_ray1(t_program *x, double *different, int *a)
{
	if (x->map.map[(int)(x->py[0] / PIXEL)]
		[(int)((x->px[0] + 2 * a[0] - 1) / PIXEL)] == '1')
		return (x->which_wall = 3 - 2 * a[0],
			x->player.new_x = x->px[0], x->player.new_y = x->py[0], 1);
	if (x->map.map[(int)((x->py[0] + 2 * a[1] - 1) / PIXEL)]
		[(int)((x->px[0] + 2 * a[0] - 1) / PIXEL)] == '1')
	{
		if (x->map.map[(int)((x->py[0] + 2 * a[1] - 1) / PIXEL)]
			[(int)(x->px[0] / PIXEL)] == '1')
			return (x->which_wall = 0, x->player.new_x = x->px[0],
				x->player.new_y = x->py[0], 1);
		return (x->which_wall = 3 - 2 * a[0], x->player.new_x = x->px[0],
			x->player.new_y = x->py[0], 1);
	}
	return (x->py[0] += different[0], x->px[0] += (2 * a[0] - 1) * PIXEL, 0);
}
