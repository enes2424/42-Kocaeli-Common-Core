/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_other2_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eates <eates@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 18:12:06 by eates             #+#    #+#             */
/*   Updated: 2023/08/20 18:12:09 by eates            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static inline void control2(t_so_long *s)
{
	int x;
	int y;

	if (s->map[(s->p.y + 16) / UNIT][(s->p.x + 32) / UNIT] == 'C' || s->map[(s->p.y + 16) / UNIT][(s->p.x - 32) / UNIT + 1] == 'C' || s->map[(s->p.y - 16) / UNIT + 1][(s->p.x + 32) / UNIT] == 'C' || s->map[(s->p.y - 16) / UNIT + 1][(s->p.x - 32) / UNIT + 1] == 'C')
	{
		control_char(s, &x, &y, 'C');
		while_loops1(s, x, y);
	}
	if (s->num_of_coin == 0 && (s->map[(s->p.y + 16) / UNIT][(s->p.x + 32) / UNIT] == 'E' || s->map[(s->p.y + 16) / UNIT][(s->p.x - 32) / UNIT + 1] == 'E' || s->map[(s->p.y - 16) / UNIT + 1][(s->p.x + 32) / UNIT] == 'E' || s->map[(s->p.y - 16) / UNIT + 1][(s->p.x - 32) / UNIT + 1] == 'E'))
	{
		control_char(s, &x, &y, 'E');
		while_loops2(s, x, y);
	}
}

int handle_key(int keycode, t_so_long *s)
{
	if (!control_keycode(keycode, s))
		return (0);
	move1(s);
	move2(s);
	control2(s);
	if (keycode == 13)
		s->tmp_player = s->back;
	else if (keycode == 0)
		s->tmp_player = s->left;
	else if (keycode == 1)
		s->tmp_player = s->front;
	else if (keycode == 2)
		s->tmp_player = s->right;
	return (0);
}

int release_key(int keycode, t_so_long *s)
{
	if (keycode == 13)
		s->keys[0] = 0;
	else if (keycode == 0)
		s->keys[1] = 0;
	else if (keycode == 1)
		s->keys[2] = 0;
	else if (keycode == 2)
		s->keys[3] = 0;
	return (1);
}

void recursive(t_control *control, char **map, int x, int y)
{
	if (map[y][x] == 'C')
		control->num_of_coin++;
	else if (map[y][x] == 'E')
		control->is_the_door_accessible = 1;
	map[y][x] = '1';
	if (y != 0 && map[y - 1][x] != '1')
		recursive(control, map, x, y - 1);
	if (map[y + 1][x] && map[y + 1][x] != '1')
		recursive(control, map, x, y + 1);
	if (x != 0 && map[y][x - 1] != '1')
		recursive(control, map, x - 1, y);
	if (map[y][x + 1] && map[y][x + 1] != '1')
		recursive(control, map, x + 1, y);
}

void control(t_so_long *s, char **map)
{
	t_control control;

	control.is_the_door_accessible = 0;
	control.num_of_coin = 0;
	recursive(&control, map, s->p.x / UNIT, s->p.y / UNIT);
	if (!control.is_the_door_accessible)
		return (ft_printf("Error\nDoor have a barrier!!!\n"), exit(1));
	if (control.num_of_coin != s->num_of_coin)
		return (ft_printf("Error\nSome coins have a barrier!!!\n"), exit(1));
	free_string_array(map);
}
