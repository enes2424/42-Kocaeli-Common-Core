/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eates <eates@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 17:32:51 by eates             #+#    #+#             */
/*   Updated: 2023/08/20 17:32:53 by eates            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int ac, char **argv)
{
	t_so_long	s;

	if (ac != 2)
	{
		ft_printf("Error\nToo many or missing arguments entered!!!\n");
		return (1);
	}
	if (!ft_strchr(argv[1], '.')
		|| ft_strncmp(ft_strchr(argv[1], '.'), ".ber", 5))
		return (ft_printf("Error\nThe file is not a ber file!!!\n"), 1);
	if (preliminary_so_long(&s, argv[1]))
		return (1);
	s.keys[0] = 0;
	s.keys[1] = 0;
	s.keys[2] = 0;
	s.keys[3] = 0;
	s.p.score = 0;
	render(&s, -1);
	mlx_put_image_to_window(s.ptr, s.win, s.front, s.p.x, s.p.y);
	mlx_hook(s.win, 17, 0, (void *)end, &s);
	mlx_hook(s.win, 2, 0, &handle_key, &s);
	mlx_hook(s.win, 3, 0, &release_key, &s);
	mlx_loop(s.ptr);
	return (0);
}
