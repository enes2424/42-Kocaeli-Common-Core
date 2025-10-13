/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_other4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eates <eates@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 21:41:33 by eates             #+#    #+#             */
/*   Updated: 2023/08/20 21:41:35 by eates            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <fcntl.h>

int	control_num_of_elemets_and_find_player(t_so_long *s)
{
	int	i;
	int	j;

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
	i = -1;
	while (s->map[++i])
	{
		j = -1;
		while (s->map[i][++j])
		{
			if (s->map[i][j] == 'P')
				return (s->p.x = j * UNIT, s->p.y = i * UNIT, 0);
		}
	}
	return (0);
}

int	preliminary_so_long(t_so_long *s, char *file)
{
	char	*tmp_map;
	char	*map_path;
	int		i;
	int		j;

	map_path = ft_strjoin("maps/", file);
	s->fd = open(map_path, O_RDONLY);
	free(map_path);
	if (s->fd < 0)
		return (ft_printf("Error\nFile not found!!!\n"), 1);
	if (create_map(s, &tmp_map))
		return (1);
	continue_init_s(s);
	if (while_loops3(s))
		return (1);
	s->width *= UNIT;
	s->height *= UNIT;
	if (control_num_of_elemets_and_find_player(s))
		return (1);
	control(s, ft_split(tmp_map, '\n'));
	free(tmp_map);
	return (generating_mlx_materials(s, &i, &j));
}
