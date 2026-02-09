/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eates <eates@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 05:36:19 by eates             #+#    #+#             */
/*   Updated: 2024/01/27 17:47:05 by eates            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
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
	if (!ft_strncmp(str, "D ", 2))
		return (equalize(str, &x->door, x));
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

void	load_doors(t_program *x)
{
	int	i;
	int	j;

	i = -1;
	while (++i < x->map.height)
	{
		j = -1;
		while (++j < x->map.width)
			if (x->map.cropped_map[i][j] == 'D')
				add_door(x, j, i);
	}
}

void	check_map(t_program *x)
{
	char	*tmp;
	int		i;
	int		j;

	x->player.x = -1;
	x->map.height = character_control(x, 0, -1, 0);
	if (x->player.x == -1)
		free_program("There is not player!!!", x, 1);
	check_map_and_changed(x);
	i = -1;
	while (++i < x->map.height)
	{
		j = ft_strlen(x->map.cropped_map[i]) - 1;
		tmp = x->map.cropped_map[i];
		x->tmp = malloc(x->map.width + 1);
		check_malloc(x, x->tmp);
		x->map.cropped_map[i] = x->tmp;
		x->tmp = NULL;
		x->map.cropped_map[i][x->map.width] = 0;
		ft_strlcpy(x->map.cropped_map[i], tmp, j + 2);
		while (++j < x->map.width)
			x->map.cropped_map[i][j] = ' ';
		free(tmp);
	}
	load_doors(x);
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
