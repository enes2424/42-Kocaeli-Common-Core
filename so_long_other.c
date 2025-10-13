/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_other.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eates <eates@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 17:43:34 by eates             #+#    #+#             */
/*   Updated: 2023/08/20 17:43:50 by eates            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	control_keycode(int keycode, t_so_long *s)
{
	if (keycode == 53)
		return (end(s), exit(0), 0);
	else
	{
		if (keycode == 13)
			s->keys[0] = 1;
		else if (keycode == 0)
			s->keys[1] = 1;
		else if (keycode == 1)
			s->keys[2] = 1;
		else if (keycode == 2)
			s->keys[3] = 1;
		else
			return (0);
		s->num_of_steps++;
		ft_printf("%d steps moved\n", s->num_of_steps);
	}
	return (1);
}

void	move1(t_so_long *s)
{
	if (s->keys[0])
	{
		if (s->map[(s->p.y + 6) / UNIT][(s->p.x + 32) / UNIT] != '1'
			&& s->map[(s->p.y + 6) / UNIT][(s->p.x + 63) / UNIT] != '1')
			s->p.y -= 10;
		else if (((s->p.y + 16) % UNIT))
			s->p.y = (UNIT * ((s->p.y + 16) / UNIT)) - 16;
		else
			s->num_of_steps--;
	}
	if (s->keys[1])
	{
		if (s->map[(s->p.y + 79) / UNIT][(s->p.x + 22) / UNIT] != '1'
			&& s->map[(s->p.y + 16) / UNIT][(s->p.x + 22) / UNIT] != '1')
			s->p.x -= 10;
		else if (((s->p.x + 32) % UNIT))
			s->p.x = (UNIT * ((s->p.x + 32) / UNIT)) - 32;
		else
			s->num_of_steps--;
	}
}

void	move2(t_so_long *s)
{
	if (s->keys[2])
	{
		if (s->map[(s->p.y - 6) / UNIT + 1][(s->p.x + 32) / UNIT] != '1'
			&& s->map[(s->p.y - 6) / UNIT + 1][(s->p.x + 63) / UNIT] != '1')
			s->p.y += 10;
		else if (((s->p.y - 16) % UNIT))
			s->p.y = (UNIT * ((s->p.y - 16) / UNIT + 1)) + 16;
		else
			s->num_of_steps--;
	}
	if (s->keys[3])
	{
		if (s->map[(s->p.y + 79) / UNIT][(s->p.x - 22) / UNIT + 1] != '1'
			&& s->map[(s->p.y + 16) / UNIT][(s->p.x - 22) / UNIT + 1] != '1')
			s->p.x += 10;
		else if (((s->p.x - 32) % UNIT))
			s->p.x = (UNIT * ((s->p.x - 32) / UNIT + 1)) + 32;
		else
			s->num_of_steps--;
	}
}

void	control_char(t_so_long *s, int *x, int *y, char c)
{
	if (s->map[(s->p.y + 16) / UNIT][(s->p.x + 32) / UNIT] == c)
	{
		*x = (s->p.x + 32) / UNIT;
		*y = (s->p.y + 16) / UNIT;
	}
	else if (s->map[(s->p.y + 16) / UNIT][(s->p.x - 32) / UNIT + 1] == c)
	{
		*x = (s->p.x - 32) / UNIT + 1;
		*y = (s->p.y + 16) / UNIT;
	}
	else if (s->map[(s->p.y - 16) / UNIT + 1][(s->p.x + 32) / UNIT] == c)
	{
		*x = (s->p.x + 32) / UNIT;
		*y = (s->p.y - 16) / UNIT + 1;
	}
	else
	{
		*x = (s->p.x - 32) / UNIT + 1;
		*y = (s->p.y - 16) / UNIT + 1;
	}
	*x *= UNIT;
	*y *= UNIT;
}

int	while_loops2(t_so_long *s, int x, int y)
{
	t_tmp	tmp;

	tmp.tmp_p_x = s->p.x + 31;
	while (++tmp.tmp_p_x < s->p.x + 63)
	{
		tmp.tmp_p_y = s->p.y + 15;
		while (++tmp.tmp_p_y < s->p.y + 79)
		{
			tmp.tmp_x = x + 44;
			while (++tmp.tmp_x < x + 50)
			{
				tmp.tmp_y = y + 41;
				while (++tmp.tmp_y < y + 52)
				{
					if (tmp.tmp_x == tmp.tmp_p_x
						&& tmp.tmp_y == tmp.tmp_p_y)
					{
						ft_printf("Congratulations you won\n");
						return (end(s), exit(0), 1);
					}
				}
			}
		}
	}
	return (0);
}
