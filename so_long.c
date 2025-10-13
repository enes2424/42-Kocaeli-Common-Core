/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eates <eates@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 14:04:35 by eates             #+#    #+#             */
/*   Updated: 2023/08/14 14:04:37 by eates            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void print_string(t_so_long *s)
{
	char *str_score;
	char *itoa_score;

	itoa_score = ft_itoa(s->p.score);
	str_score = ft_strjoin("Score : ", itoa_score);
	mlx_string_put(s->ptr, s->win, UNIT / 2 - 2, UNIT / 2 - 10, 0, str_score);
	free(itoa_score);
	free(str_score);
}

void render(t_so_long *s, int i)
{
	int j;
	void *tmp;

	mlx_clear_window(s->ptr, s->win);
	while (s->map[++i])
	{
		j = -1;
		while (s->map[i][++j])
		{
			tmp = s->grass;
			mlx_put_image_to_window(s->ptr, s->win, tmp, UNIT * j, UNIT * i);
			if (s->map[i][j] == '1')
				tmp = s->wall;
			else if (s->map[i][j] == 'C')
				tmp = s->coin;
			else if (s->map[i][j] == 'E')
				tmp = s->door;
			else
				continue;
			mlx_put_image_to_window(s->ptr, s->win, tmp, UNIT * j, UNIT * i);
		}
	}
	print_string(s);
}

int while_loops1(t_so_long *s, int x_coin, int y_coin)
{
	t_tmp tmp;

	tmp.tmp_p_x = s->p.x + 31;
	while (++tmp.tmp_p_x < s->p.x + 63)
	{
		tmp.tmp_p_y = s->p.y + 15;
		while (++tmp.tmp_p_y < s->p.y + 79)
		{
			tmp.tmp_x = x_coin + 29;
			while (++tmp.tmp_x < x_coin + 65)
			{
				tmp.tmp_y = y_coin + 27;
				while (++tmp.tmp_y < y_coin + 66)
				{
					if (tmp.tmp_x == tmp.tmp_p_x && tmp.tmp_y == tmp.tmp_p_y)
					{
						s->map[y_coin / UNIT][x_coin / UNIT] = '0';
						return (s->num_of_coin--, s->p.score += 500, 1);
					}
				}
			}
		}
	}
	return (0);
}

void end(t_so_long *s)
{
	if (s->back)
		mlx_destroy_image(s->ptr, s->back);
	if (s->coin)
		mlx_destroy_image(s->ptr, s->coin);
	if (s->grass)
		mlx_destroy_image(s->ptr, s->grass);
	if (s->door)
		mlx_destroy_image(s->ptr, s->door);
	if (s->right)
		mlx_destroy_image(s->ptr, s->right);
	if (s->front)
		mlx_destroy_image(s->ptr, s->front);
	if (s->left)
		mlx_destroy_image(s->ptr, s->left);
	if (s->wall)
		mlx_destroy_image(s->ptr, s->wall);
	if (s->win)
		mlx_destroy_window(s->ptr, s->win);
	free_string_array(s->map);
	close(s->fd);
	exit(0);
}
