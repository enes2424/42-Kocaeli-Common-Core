/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eates <eates@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 05:36:21 by eates             #+#    #+#             */
/*   Updated: 2024/01/27 18:33:00 by eates            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include "../libft/libft.h"
#include <unistd.h>

void	check_arg(int ac, char **av)
{
	char	*control;

	if (ac != 2)
		return (ft_putendl_fd("number of arguments is incorrect!!!", 2)
			, exit(1));
	control = ft_strnstr(av[1], ".cub", ft_strlen(av[1]));
	if (!control || control[4])
		return (ft_putendl_fd("the file is not a cub file!!!", 2)
			, exit(1));
}

void	add_door(t_program *x, int dx, int dy)
{
	t_door	*new;

	new = ft_calloc(1, sizeof(t_door));
	check_malloc(x, new);
	new->x = dx;
	new->y = dy;
	new->next = x->doors;
	x->doors = new;
}

void	init(t_program *x)
{
	x->wall.ea = NULL;
	x->wall.no = NULL;
	x->wall.so = NULL;
	x->wall.we = NULL;
	x->colors.f = NULL;
	x->colors.c = NULL;
	x->door = NULL;
	x->tmp = NULL;
	x->speed = 20;
	x->multipler = 1;
	x->map.map = NULL;
	x->map.copy = NULL;
	x->mlx.mdoor = NULL;
	x->mlx.door = NULL;
	x->map.width = 0;
	x->player.keys[0] = 0;
	x->player.keys[1] = 0;
	x->player.keys[2] = 0;
	x->player.keys[3] = 0;
	x->player.keys[4] = 0;
	x->player.keys[5] = 0;
	x->list = NULL;
	x->doors = NULL;
	init_mlx(x);
}

void	init_mlx(t_program *x)
{
	int	i;

	x->mlx.win = NULL;
	x->mlx.player = NULL;
	x->mlx.wall = NULL;
	x->mlx.floor = NULL;
	x->mlx.walls[0] = NULL;
	x->mlx.walls[1] = NULL;
	x->mlx.walls[2] = NULL;
	x->mlx.walls[3] = NULL;
	x->mlx.screen = NULL;
	i = -1;
	while (++i < 12)
		x->mlx.animation[i] = NULL;
}

void	create_map(t_program *x, int fd)
{
	char	line[100];
	int		i;

	i = read(fd, line, 99);
	if (i <= 0)
		return (close(fd), free_program("the map cannot be read!!!", x, 1));
	line[i] = 0;
	while (i)
	{
		x->tmp = ft_strjoin(x->tmp, line);
		if (!x->tmp)
			return (close(fd),
				free_program(ALLOC_ERR, x, 1));
		i = read(fd, line, 99);
		line[i] = 0;
	}
	if (!close(fd) && !control(x))
		free_program(ALLOC_ERR, x, 1);
	if ((int)ft_nb_words(x->tmp, '\n', 1) == -2)
		free_program("map is wrong!!", x, 1);
	x->map.map = ft_split(x->tmp, '\n');
	check_malloc(x, x->map.map);
	x->map.copy = ft_split(x->tmp, '\n');
	check_malloc(x, x->map.copy);
	special_free((void **)&x->tmp);
}
