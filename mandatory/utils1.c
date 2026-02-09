/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eates <eates@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 05:36:19 by eates             #+#    #+#             */
/*   Updated: 2024/01/28 19:27:08 by eates            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "../libft/libft.h"

char	*control2(t_program *x, char *str)
{
	while (ft_isspaces(*str))
		str++;
	if (!ft_strncmp(str, "NO ", 3))
		return (equalize(str, &x->wall.no, x));
	if (!ft_strncmp(str, "SO ", 3))
		return (equalize(str, &x->wall.so, x));
	if (!ft_strncmp(str, "WE ", 3))
		return (equalize(str, &x->wall.we, x));
	if (!ft_strncmp(str, "EA ", 3))
		return (equalize(str, &x->wall.ea, x));
	if (!ft_strncmp(str, "F ", 2))
		return (equalize(str, &x->colors.f, x));
	return (equalize(str, &x->colors.c, x));
}

char	*equalize(char *str, char **str2, t_program *x)
{
	char	*tmp;
	int		count;
	int		flag;

	flag = (!ft_strncmp(str, "F ", 2) || !ft_strncmp(str, "C ", 2));
	str += 2;
	while (ft_isspaces(*str) && *str != '\n')
		str++;
	tmp = str;
	if (flag)
	{
		count = 0;
		while (count < 3 && *str && *str != '\n')
			count += (*str++ == ',');
		if (count != 2)
			free_program("The map contains incomplete information!!!", x, 1);
	}
	else
		while (*str && !ft_isspaces(*str))
			str++;
	*str2 = ft_substr(tmp, 0, str - tmp);
	if (!*str2)
		free_program(ALLOC_ERR, x, 1);
	return (str);
}

void	close_map_control(t_program *x, int i, int j)
{
	int	control_i;
	int	control_j;

	control_i = i - 1;
	while (control_i <= i + 1)
	{
		control_j = j - 1;
		while (control_j <= j + 1)
		{
			if (control_i == -1 || control_j == -1 || !x->map.map[control_i]
				|| control_j >= (int)ft_strlen(x->map.map[control_i])
				|| x->map.map[control_i][control_j] == ' ')
				free_program("Unclose map!!!", x, 1);
			control_j++;
		}
		control_i++;
	}
}

void	character_control2(t_program *x, int is_there_player, int i)
{
	int	j;

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
		else if (!in_set(x->map.map[i][j], " 10"))
			free_program("Map contains unrecognized element!!!", x, 1);
		if (x->map.map[i][j] != '1' && x->map.map[i][j] != ' ')
			close_map_control(x, i, j);
	}
	if (j > x->map.width)
		x->map.width = j;
}

int	character_control(t_program *x)
{
	int	i;

	i = -1;
	x->player.x = -1;
	while (x->map.map[++i])
		character_control2(x, 0, i);
	if (x->player.x == -1)
		free_program("There is not player!!!", x, 1);
	return (i);
}
