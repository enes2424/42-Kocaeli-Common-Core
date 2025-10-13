/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_other4_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eates <eates@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 21:41:33 by eates             #+#    #+#             */
/*   Updated: 2023/08/20 21:41:35 by eates            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"
#include <fcntl.h>

int	control_player_or_enemy(t_so_long *s, int i, char c)
{
	int	j;
	int	k;

	k = 0;
	while (s->map[++i])
	{
		j = -1;
		while (s->map[i][++j])
		{
			if (c == 'P' && s->map[i][j] == 'P')
				return (s->p.x = j * UNIT, s->p.y = i * UNIT, 0);
			else if (c == 'S' && s->map[i][j] == 'S')
			{
				s->e[k].x = j * UNIT;
				s->e[k++].y = i * UNIT;
			}
		}
	}
	return (0);
}

int	control_num_of_elemets_and_find_player(t_so_long *s)
{
	s->width *= UNIT;
	s->height *= UNIT;
	if (s->num_of_player == 0)
		return (ft_printf("Error\nPlayer not found!!!\n"), close(s->fd), 1);
	if (s->num_of_player != 1)
		return (ft_printf("Error\nMultiple players found!!!\n"), close(s->fd), 1);
	if (s->num_of_exit == 0)
		return (ft_printf("Error\nDoor not found!!!\n"), close(s->fd), 1);
	if (s->num_of_exit != 1)
		return (ft_printf("Error\nMultiple doors found!!!\n"), close(s->fd), 1);
	if (s->num_of_coin == 0)
		return (ft_printf("Error\nCoin not found!!!\n"), close(s->fd), 1);
	control_player_or_enemy(s, -1, 'P');
	control_player_or_enemy(s, -1, 'S');
	return (0);
}

int	preliminary_so_long(t_so_long *s, char *file)
{
	char	*map_path;
	int		i;
	int		j;

	map_path = ft_strjoin("bonus/maps/", file);
	s->fd = open(map_path, O_RDONLY);
	free(map_path);
	if (s->fd < 0)
		return (ft_printf("Error\nFile not found!!!\n"), 1);
	if (create_map(s, &s->tmp_map))
		return (1);
	continue_init_s(s);
	if (while_loops3(s))
		return (1);
	s->e = malloc(s->num_of_enemy * sizeof(t_enemy));
	i = -1;
	while (++i < s->num_of_enemy)
	{
		s->e[i].is_left = 1;
		s->e[i].is_right = 0;
	}
	if (control_num_of_elemets_and_find_player(s))
		return (1);
	control(s, ft_split(s->tmp_map, '\n'));
	return (generating_mlx_materials(s, &i, &j));
}

int	while_loops3(t_so_long *s)
{
	int	i;
	int	j;

	i = -1;
	while (s->map[++i])
	{
		j = -1;
		while (s->map[i][++j])
		{
			if (s->width <= j)
			{
				ft_printf("Error\nMap is not rectangular!!!\n");
				return (close(s->fd), 1);
			}
			control_map_and_count_element(s, i, j);
		}
		if (j != s->width)
		{
			ft_printf("Error\nMap is not rectangular!!!\n");
			return (close(s->fd), 1);
		}
	}
	return (0);
}
