/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eates <eates@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 17:32:51 by eates             #+#    #+#             */
/*   Updated: 2023/08/20 17:32:53 by eates            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static inline int	while_loops4(t_so_long *s, t_tmp *tmp,
	int x_enemy, int y_enemy)
{
	tmp->tmp_p_x = s->p.x + 31;
	while (++tmp->tmp_p_x < s->p.x + 63)
	{
		tmp->tmp_p_y = s->p.y + 15;
		while (++tmp->tmp_p_y < s->p.y + 79)
		{
			tmp->tmp_x = x_enemy + 31;
			while (++tmp->tmp_x < x_enemy + 63)
			{
				tmp->tmp_y = y_enemy + 15;
				while (++tmp->tmp_y < y_enemy + 79)
				{
					if (tmp->tmp_x == tmp->tmp_p_x
						&& tmp->tmp_y == tmp->tmp_p_y)
					{
						s->map[y_enemy / UNIT][x_enemy / UNIT] = '0';
						ft_printf("You hit the zombie\n");
						return (end(s), 1);
					}
				}
			}
		}
	}
	return (0);
}

static inline void	put_enemy(t_so_long	*s, int i)
{
	if (s->e[i].is_left)
	{
		mlx_put_image_to_window(s->ptr, s->win,
			s->enemy_left, s->e[i].x, s->e[i].y);
		s->e[i].x -= 3;
		if (s->map[s->e[i].y / UNIT][(s->e[i].x + 34) / UNIT] == '1')
		{
			s->e[i].is_left = 0;
			s->e[i].is_right = 1;
		}
	}
	else if (s->e[i].is_right)
	{
		mlx_put_image_to_window(s->ptr, s->win,
			s->enemy_right, s->e[i].x, s->e[i].y);
		s->e[i].x += 3;
		if (s->map[s->e[i].y / UNIT][(s->e[i].x - 34) / UNIT + 1] == '1')
		{
			s->e[i].is_left = 1;
			s->e[i].is_right = 0;
		}
	}
}

static inline void	enemy(t_so_long	*s)
{
	int		i;
	t_tmp	tmp;

	i = -1;
	while (++i < s->num_of_enemy)
	{
		while_loops4(s, &tmp, s->e[i].x, s->e[i].y);
		put_enemy(s, i);
	}
}

int	extra(t_so_long *s)
{
	int	i;

	i = -1;
	render(s, -1);
	enemy(s);
	i = 0;
	if (s->creeper_y == 0 && s->creeper_x != s->width - UNIT)
		s->creeper_x += 2;
	if (s->creeper_x == s->width - UNIT && s->creeper_y != s->height - UNIT)
		s->creeper_y += 2;
	if (s->creeper_y == s->height - UNIT && s->creeper_x != 0)
		s->creeper_x -= 2;
	if (s->creeper_x == 0)
	{
		s->creeper_y -= 2;
		if (s->creeper_y == 0)
			return (ft_printf("TIME IS UP\n"), end(s), 1);
	}
	s->index_creeper++;
	if (s->index_creeper == 60)
		s->index_creeper = 0;
	return (1);
}

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
	s.tmp_player = s.front;
	mlx_hook(s.win, 17, 0, (void *)end, &s);
	mlx_hook(s.win, 2, 0, &handle_key, &s);
	mlx_hook(s.win, 3, 0, &release_key, &s);
	mlx_loop_hook(s.ptr, &extra, &s);
	mlx_loop(s.ptr);
	return (0);
}
