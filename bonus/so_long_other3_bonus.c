/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_other3_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eates <eates@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 19:29:21 by eates             #+#    #+#             */
/*   Updated: 2023/08/20 19:29:23 by eates            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static inline void	generating_mlx_materials_extra(t_so_long *s, int *x, int *y)
{
	s->enemy_left = mlx_xpm_file_to_image(s->ptr,
			"bonus/textures/enemy_left.xpm", x, y);
	s->enemy_right = mlx_xpm_file_to_image(s->ptr,
			"bonus/textures/enemy_right.xpm", x, y);
	s->creeper[0] = mlx_xpm_file_to_image(s->ptr,
			"bonus/textures/green_creeper.xpm", x, y);
	s->creeper[1] = mlx_xpm_file_to_image(s->ptr,
			"bonus/textures/blue_creeper.xpm", x, y);
	s->creeper[2] = mlx_xpm_file_to_image(s->ptr,
			"bonus/textures/red_creeper.xpm", x, y);
	s->creeper[3] = mlx_xpm_file_to_image(s->ptr,
			"bonus/textures/purple_creeper.xpm", x, y);
	if (!s->front || !s->grass || !s->coin
		|| !s->wall || !s->right || !s->left
		|| !s->back || !s->door || !s->creeper[0]
		|| !s->creeper[1] || !s->creeper[2]
		|| !s->creeper[3] || !s->enemy_right
		|| !s->enemy_left)
	{
		ft_printf("Error\n");
		ft_printf("One or more xpm files could not be found or converted!!!\n");
		end(s);
	}
}

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
	generating_mlx_materials_extra(s, x, y);
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
	s->num_of_enemy = 0;
	s->keys[0] = 0;
	s->keys[1] = 0;
	s->keys[2] = 0;
	s->keys[3] = 0;
	s->p.score = 0;
	s->creeper_x = 0;
	s->creeper_y = 0;
	s->creeper = malloc(sizeof(void *) * 4);
	s->index_creeper = 0;
}

void	control_map_and_count_element(t_so_long *s, int i, int j)
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
	else if (s->map[i][j] == 'S')
		s->num_of_enemy++;
	else if (s->map[i][j] != '1' && s->map[i][j] != '0' && s->map[i][j] != 'S')
	{
		ft_printf("Error\nUnrecognized character found on the map.!!!\n");
		return (close(s->fd), exit(1));
	}
}
