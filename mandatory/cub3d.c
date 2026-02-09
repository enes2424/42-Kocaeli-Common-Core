/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eates <eates@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 18:27:20 by eates             #+#    #+#             */
/*   Updated: 2024/01/29 14:14:36 by eates            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <fcntl.h>

int	main(int ac, char **av)
{
	t_program	x;

	check_arg(ac, av);
	init(&x);
	create_map(&x, open(av[1], O_RDONLY));
	play_program(&x);
	return (0);
}
