/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_other3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eates <eates@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 19:29:21 by eates             #+#    #+#             */
/*   Updated: 2023/08/20 19:29:23 by eates            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	generating_mlx_materials(t_so_long *s, int *x, int *y)
{
	s->ptr = mlx_init();
	if (!s->ptr)
		return (ft_printf("Error\nPointer not inited!!!\n"), close(s->fd), 1);
	s->win = mlx_new_window(s->ptr, s->width, s->height, "So_long");
	if (!s->win)
		return (ft_printf("Error\nWindow not opened!!!\n"), close(s->fd), 1);
	s->front = mlx_xpm_file_to_image(s->ptr, "textures/front.xpm", x, y);
	s->grass = mlx_xpm_file_to_image(s->ptr, "textures/grass.xpm", x, y);
	s->coin = mlx_xpm_file_to_image(s->ptr, "textures/coin.xpm", x, y);
	s->wall = mlx_xpm_file_to_image(s->ptr, "textures/wall.xpm", x, y);
	s->right = mlx_xpm_file_to_image(s->ptr, "textures/right.xpm", x, y);
	s->left = mlx_xpm_file_to_image(s->ptr, "textures/left.xpm", x, y);
	s->back = mlx_xpm_file_to_image(s->ptr, "textures/back.xpm", x, y);
	s->door = mlx_xpm_file_to_image(s->ptr, "textures/door.xpm", x, y);
	if (!s->front || !s->grass || !s->coin
		|| !s->wall || !s->right || !s->left
		|| !s->back || !s->door)
	{
		ft_printf("Error\n");
		ft_printf("One or more xpm files could not be found or converted!!!\n");
		return (end(s), 1);
	}
	return (0);
}

int	create_map(t_so_long *s, char **tmp_map)
{
	char	*tmp_tmp_map;
	char	*line;

	line = get_next_line(s->fd);
	if (!line)
		return (ft_printf("Error\nEmpty map!!!\n"), close(s->fd), 1);
	*tmp_map = ft_strdup("");
	while (line)
	{
		tmp_tmp_map = ft_strjoin(*tmp_map, line);
		free(*tmp_map);
		free(line);
		line = get_next_line(s->fd);
		*tmp_map = tmp_tmp_map;
	}
	s->map = ft_split(*tmp_map, '\n');
	if (!s->map)
		return (ft_printf("Error\nMap not splited!!!\n"), close(s->fd), 1);
	return (0);
}

void	continue_init_s(t_so_long *s)
{
	int	i;
	int	j;

	j = 0;
	while (s->map[0][j])
		j++;
	i = 0;
	while (s->map[i])
		i++;
	s->width = j;
	s->height = i;
	s->num_of_steps = 0;
	s->num_of_coin = 0;
	s->num_of_player = 0;
	s->num_of_exit = 0;
}

static void	control_map_and_count_element(t_so_long *s, int i, int j)
{
	if (i == 0 || i == s->height - 1
		|| j == 0 || j == s->width - 1)
	{
		if (s->map[i][j] != '1')
		{
			ft_printf("Error\n");
			ft_printf("Walls do not completely enclose the map!!!\n");
			return (close(s->fd), exit(1));
		}
	}
	if (s->map[i][j] == 'P')
		s->num_of_player++;
	else if (s->map[i][j] == 'E')
		s->num_of_exit++;
	else if (s->map[i][j] == 'C')
		s->num_of_coin++;
	else if (s->map[i][j] != '1' && s->map[i][j] != '0')
	{
		ft_printf("Error\nUnrecognized character found on the map.!!!\n");
		return (close(s->fd), exit(1));
	}
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
