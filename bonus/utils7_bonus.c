/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils7_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eates <eates@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 05:35:57 by eates             #+#    #+#             */
/*   Updated: 2024/01/27 18:36:18 by eates            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include <math.h>
#include "../libft/libft.h"
#include "../minilibx/mlx.h"

int	handle2(t_program *x)
{
	int		px;
	int		py;
	int		i;
	char	flag;
	double	angle;

	px = x->speed * x->multipler * cos(PI * (x->angle + 90) / 180.0);
	py = x->speed * x->multipler * sin(PI * (x->angle + 90) / 180.0);
	i = -1;
	while (++i < 4)
	{
		if (!x->player.keys[i])
			continue ;
		angle = x->angle + (225 - 135 * !(i % 2) + 45 * i);
		throwing_ray(x, angle, tan(PI * angle / 180.0));
		flag = (x->player.new_x - x->player.x) * (x->player.new_x - x->player.x)
			+ (x->player.new_y - x->player.y) * (x->player.new_y - x->player.y)
			<= x->speed * x->multipler * x->speed * x->multipler;
		x->player.y = flag * x->player.new_y + !flag
			* (x->player.y + (2 * (i % 2) - 1) * ((i < 2) * py + (i > 1) * px));
		x->player.x = flag * x->player.new_x + !flag * (x->player.x \
		+ (1 - 2 * ((i % 2) ^ ((i / 2) % 2))) * ((i < 2) * px + (i > 1) * py));
	}
	x->angle = (x->angle + 10 * (x->player.keys[4] - x->player.keys[5])) % 360;
	return (1);
}

int	release(int key, t_program *x)
{
	if (key == W)
		x->player.keys[0] = 0;
	else if (key == S)
		x->player.keys[1] = 0;
	else if (key == A)
		x->player.keys[2] = 0;
	else if (key == D)
		x->player.keys[3] = 0;
	else if (key == L)
		x->player.keys[4] = 0;
	else if (key == R)
		x->player.keys[5] = 0;
	else if (key == SHIFT)
		x->multipler = 1;
	return (1);
}

void	free_program(char *str, t_program *x, int status)
{
	int	i;

	ft_putendl_fd(str, 2);
	free(x->tmp);
	free_string_array(x->map.map);
	free_string_array(x->map.copy);
	linkedlistclear(x->list);
	doorlistclear(x->doors);
	free(x->wall.ea);
	free(x->wall.no);
	free(x->wall.so);
	free(x->wall.we);
	free(x->colors.f);
	free(x->colors.c);
	free(x->door);
	if (!x->mlx.ptr)
		exit(status);
	mlx_destroy(x);
	i = -1;
	while (++i < 12)
		if (x->mlx.animation[i])
			mlx_image_destroy(x->mlx.ptr, x->mlx.animation[i]);
	exit(status);
}

void	mlx_destroy(t_program *x)
{
	if (x->mlx.win)
		mlx_destroy_window(x->mlx.ptr, x->mlx.win);
	if (x->mlx.player)
		mlx_destroy_image(x->mlx.ptr, x->mlx.player);
	if (x->mlx.wall)
		mlx_destroy_image(x->mlx.ptr, x->mlx.wall);
	if (x->mlx.floor)
		mlx_destroy_image(x->mlx.ptr, x->mlx.floor);
	if (x->mlx.mdoor)
		mlx_destroy_image(x->mlx.ptr, x->mlx.mdoor);
	if (x->mlx.walls[0])
		mlx_image_destroy(x->mlx.ptr, x->mlx.walls[0]);
	if (x->mlx.walls[1])
		mlx_image_destroy(x->mlx.ptr, x->mlx.walls[1]);
	if (x->mlx.walls[2])
		mlx_image_destroy(x->mlx.ptr, x->mlx.walls[2]);
	if (x->mlx.walls[3])
		mlx_image_destroy(x->mlx.ptr, x->mlx.walls[3]);
	if (x->mlx.screen)
		mlx_image_destroy(x->mlx.ptr, x->mlx.screen);
	if (x->mlx.door)
		mlx_image_destroy(x->mlx.ptr, x->mlx.door);
}

void	mlx_image_destroy(void *ptr, t_mlx_image *image)
{
	mlx_destroy_image(ptr, image->img);
	free(image);
}
