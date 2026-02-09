/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils9_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eates <eates@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 17:46:30 by eates             #+#    #+#             */
/*   Updated: 2024/01/28 19:23:53 by eates            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include "../libft/libft.h"
#include "../minilibx/mlx.h"

int	character_control(t_program *x, int is_there_player, int i, int j)
{
	while (x->map.map[++i])
	{
		j = -1;
		while (x->map.map[i][++j])
		{
			if (in_set(x->map.map[i][j], "NSWE"))
			{
				if (is_there_player)
					free_program("Map contains multiple players!!!", x, 1);
				is_there_player = 1;
				x->angle = (x->map.map[i][j] == 'S') * 180
					+ (x->map.map[i][j] == 'E') * (-90)
					+ (x->map.map[i][j] == 'W') * (90);
				x->player.x = j * PIXEL + 75;
				x->player.y = i * PIXEL + 75;
			}
			else if (!in_set(x->map.map[i][j], " 10D"))
				free_program("Map contains unrecognized element!!!", x, 1);
			else if (x->map.map[i][j] != '1' && x->map.map[i][j] != ' ')
				close_map_control(x, i, j);
		}
		if (j > x->map.width)
			x->map.width = j;
	}
	return (i);
}

static void	check_map_and_changed2(t_program *x)
{
	char	*tmp;
	int		i;

	while (control4(x->map.cropped_map, 0))
	{
		x->player.x -= PIXEL;
		i = -!!x->map.width--;
		while (++i < x->map.height)
		{
			tmp = ft_strdup(x->map.cropped_map[i] + 1);
			check_malloc(x, tmp);
			free(x->map.cropped_map[i]);
			x->map.cropped_map[i] = tmp;
		}
	}
	while (control4(x->map.cropped_map, x->map.width - 1))
	{
		x->map.width--;
		i = -1;
		while (x->map.cropped_map[++i])
		{
			if ((int)ft_strlen(x->map.cropped_map[i]) > x->map.width)
				x->map.cropped_map[i][x->map.width] = 0;
		}
	}
}

void	check_map_and_changed(t_program *x)
{
	path_finder(x, x->map.copy, x->player.y / PIXEL, x->player.x / PIXEL);
	x->map.copy = re_create(x->map.map, x->map.copy);
	x->map.cropped_map = x->map.map;
	while (control3(x->map.cropped_map[0]) && x->map.cropped_map++)
		x->player.y -= PIXEL * !!x->map.height--;
	while (control3(x->map.cropped_map[x->map.height - 1]))
		special_free((void **)&x->map.cropped_map[--x->map.height]);
	check_map_and_changed2(x);
}

int	game_loop(t_program *x)
{
	static int	i = 0;
	int			a;
	int			b;

	if (i % 8 == 0)
	{
		mlx_image_destroy(x->mlx.ptr, x->mlx.door);
		x->mlx.door = create_door_img(x, &a, &b, i / 16);
		render(x);
	}
	i = (i + 1) % 192;
	return (1);
}

void	play_program(t_program *x)
{
	init_program(x);
	if (!x->mlx.win || !x->mlx.player || !x->mlx.wall || !x->mlx.floor
		|| !x->mlx.walls[0] || !x->mlx.walls[1] || !x->mlx.door
		|| !x->mlx.walls[2] || !x->mlx.walls[3] || !x->mlx.mdoor
		|| !x->mlx.animation[0] || !x->mlx.animation[1] || !x->mlx.animation[2]
		|| !x->mlx.animation[3] || !x->mlx.animation[4] || !x->mlx.animation[5]
		|| !x->mlx.animation[6] || !x->mlx.animation[7] || !x->mlx.animation[8] \
	|| !x->mlx.animation[9] || !x->mlx.animation[10] || !x->mlx.animation[11])
		free_program(ALLOC_ERR, x, 1);
	create_sky_and_floor(x);
	mlx_hook(x->mlx.win, 17, 0, exit_x, x);
	mlx_hook(x->mlx.win, 2, 0, handle, x);
	mlx_hook(x->mlx.win, 3, 0, release, x);
	mlx_mouse_get_pos(x->mlx.win, &x->mouse_x, &x->mouse_y);
	mlx_hook(x->mlx.win, 6, 0, handle_mouse_move, x);
	mlx_loop_hook(x->mlx.ptr, game_loop, x);
	mlx_loop(x->mlx.ptr);
}
