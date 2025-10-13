/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eates <eates@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 14:00:51 by eates             #+#    #+#             */
/*   Updated: 2023/08/14 14:00:53 by eates            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_BONUS_H
# define SO_LONG_BONUS_H

# include "../libft/libft.h"
# include "../minilibx/mlx.h"

# define UNIT 96

typedef struct s_player
{
	int	x;
	int	y;
	int	score;
}	t_player;

typedef struct s_enemy
{
	int		x;
	int		y;
	int		is_right;
	int		is_left;
}	t_enemy;

typedef struct s_so_long
{
	void		*ptr;
	void		*win;
	void		*wall;
	void		*coin;
	void		*grass;
	void		*front;
	void		*right;
	void		*left;
	void		*back;
	void		*door;
	void		**creeper;
	void		*tmp_player;
	void		*enemy_left;
	void		*enemy_right;
	t_player	p;
	t_enemy		*e;
	char		**map;
	char		*tmp_map;
	int			index_creeper;
	int			creeper_x;
	int			creeper_y;
	int			keys[4];
	int			num_of_steps;
	int			num_of_player;
	int			num_of_coin;
	int			num_of_exit;
	int			num_of_enemy;
	int			fd;
	int			width;
	int			height;
}	t_so_long;

typedef struct s_control
{
	int	num_of_coin;
	int	is_the_door_accessible;
}	t_control;

typedef struct s_tmp
{
	int	tmp_p_x;
	int	tmp_p_y;
	int	tmp_x;
	int	tmp_y;
}	t_tmp;

void	render(t_so_long *s, int i);
int		handle_key(int keycode, t_so_long *s);
int		release_key(int keycode, t_so_long *s);
void	control(t_so_long *s, char **map);
int		preliminary_so_long(t_so_long *s, char *file);
void	end(t_so_long *s);
int		while_loops1(t_so_long *s, int x_coin, int y_coin);
int		while_loops2(t_so_long *s, int x, int y);
int		while_loops3(t_so_long *s);
void	control_char(t_so_long *s, int *x, int *y, char c);
void	move1(t_so_long *s);
void	move2(t_so_long *s);
int		control_keycode(int keycode, t_so_long *s);
int		control_num_of_elemets_and_find_player(t_so_long *s);
int		create_map(t_so_long *s, char **tmp_map);
void	continue_init_s(t_so_long *s);
int		generating_mlx_materials(t_so_long *s, int *x, int *y);
void	control_map_and_count_element(t_so_long *s, int i, int j);

#endif
