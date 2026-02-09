/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eates <eates@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 05:36:15 by eates             #+#    #+#             */
/*   Updated: 2024/01/27 19:46:29 by eates            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include "../libft/libft.h"

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

int	handle_mouse_move(int mx, int my, t_program *x)
{
	int	diff;

	(void)my;
	diff = x->mouse_x - mx;
	if (!diff && x->mouse_x > 1800)
		diff = -20;
	else if (!diff && x->mouse_x <= 0)
		diff = 20;
	x->angle = (x->angle + diff / 4) % 360;
	x->mouse_x = mx;
	return (0);
}
