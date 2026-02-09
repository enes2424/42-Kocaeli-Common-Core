/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eates <eates@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 05:36:15 by eates             #+#    #+#             */
/*   Updated: 2024/01/27 20:20:54 by eates            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "../libft/libft.h"
#include "../minilibx/mlx.h"

void	path_finder(t_program *x, char **map, int i, int j)
{
	if (i == -1 || j == -1 || !map[i]
		|| j >= (int)ft_strlen(map[i]) || map[i][j] == ' ')
		free_program("There is a place where player can exit the map!!!", x, 1);
	if (map[i][j] == '1' || map[i][j] == '2')
	{
		map[i][j] = '2';
		return ;
	}
	map[i][j] = '2';
	path_finder(x, map, i, j - 1);
	path_finder(x, map, i, j + 1);
	path_finder(x, map, i - 1, j);
	path_finder(x, map, i + 1, j);
}

char	**re_create(char **map, char **copy_map)
{
	int	i;
	int	j;

	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
			if (copy_map[i][j] != '2')
				map[i][j] = ' ';
	}
	return (free_string_array(copy_map));
}

int	control3(char *str)
{
	while (*str == ' ')
		str++;
	return (!*str);
}

int	control4(char **map, int x)
{
	int	i;

	i = -1;
	while (map[++i])
		if (x < (int)ft_strlen(map[i]) && map[i][x] != ' ')
			return (0);
	return (1);
}

void	play_program(t_program *x)
{
	init_program(x);
	if (!x->mlx.win || !x->mlx.walls[0] || !x->mlx.walls[1]
		|| !x->mlx.walls[2] || !x->mlx.walls[3])
		free_program(ALLOC_ERR, x, 1);
	create_sky_and_floor(x);
	render(x);
	mlx_hook(x->mlx.win, 17, 0, exit_x, x);
	mlx_hook(x->mlx.win, 2, 0, handle, x);
	mlx_hook(x->mlx.win, 3, 0, release, x);
	mlx_loop(x->mlx.ptr);
}
