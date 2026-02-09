/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eates <eates@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 18:27:20 by eates             #+#    #+#             */
/*   Updated: 2024/01/27 18:38:02 by eates            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include <stdio.h>
#include <fcntl.h>

static void	print_info(t_program *x)
{
	int	i;

	i = -1;
	printf("NO -> [%s]\n", x->wall.no);
	printf("SO -> [%s]\n", x->wall.so);
	printf("WE -> [%s]\n", x->wall.we);
	printf("EA -> [%s]\n", x->wall.ea);
	printf("F -> [%s]\n", x->colors.f);
	printf("C -> [%s]\n", x->colors.c);
	printf("D -> [%s]\n", x->door);
	printf("width -> %d\n", x->map.width);
	printf("height -> %d\n", x->map.height);
	while (x->map.cropped_map[++i])
		printf("%s\n", x->map.cropped_map[i]);
}

t_door	*search(t_door *lst, int x, int y)
{
	while (lst)
	{
		if (lst->x == x && lst->y == y)
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}

int	main(int ac, char **av)
{
	t_program	x;

	check_arg(ac, av);
	init(&x);
	create_map(&x, open(av[1], O_RDONLY));
	check_map(&x);
	print_info(&x);
	play_program(&x);
	return (0);
}
