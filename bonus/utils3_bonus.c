/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eates <eates@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 05:36:12 by eates             #+#    #+#             */
/*   Updated: 2024/01/29 13:16:29 by eates            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include "../minilibx/mlx.h"
#include "../libft/libft.h"

t_mlx_image	*create_door_img(t_program *x, int *a, int *b, int status)
{
	t_mlx_image	*door;
	int			i;
	int			j;

	door = mlx_image_init(x->mlx.ptr, x->door, a, b);
	check_malloc(x, door);
	i = -1;
	while (++i < PIXEL)
	{
		j = -1;
		while (++j < PIXEL)
		{
			if (*((unsigned int *)(x->mlx.animation[status]->addr
					+ i * PIXEL * 4 + j * 4)) != 4278190080)
			{
				*((unsigned int *)(door->addr + i
							* PIXEL * 4 + j * 4))
					= *((unsigned int *)(x->mlx.animation[status]->addr
							+ i * PIXEL * 4 + j * 4));
			}
		}
	}
	return (door);
}

void	mlx_animation_init(void *ptr, t_mlx_image **images, int *a, int *b)
{
	images[0] = mlx_image_init(ptr, "bonus/gamer_gifs/1.xpm", a, b);
	images[1] = mlx_image_init(ptr, "bonus/gamer_gifs/2.xpm", a, b);
	images[2] = mlx_image_init(ptr, "bonus/gamer_gifs/3.xpm", a, b);
	images[3] = mlx_image_init(ptr, "bonus/gamer_gifs/4.xpm", a, b);
	images[4] = mlx_image_init(ptr, "bonus/gamer_gifs/5.xpm", a, b);
	images[5] = mlx_image_init(ptr, "bonus/gamer_gifs/6.xpm", a, b);
	images[6] = mlx_image_init(ptr, "bonus/gamer_gifs/7.xpm", a, b);
	images[7] = mlx_image_init(ptr, "bonus/gamer_gifs/8.xpm", a, b);
	images[8] = mlx_image_init(ptr, "bonus/gamer_gifs/9.xpm", a, b);
	images[9] = mlx_image_init(ptr, "bonus/gamer_gifs/10.xpm", a, b);
	images[10] = mlx_image_init(ptr, "bonus/gamer_gifs/11.xpm", a, b);
	images[11] = mlx_image_init(ptr, "bonus/gamer_gifs/12.xpm", a, b);
}

void	init_program(t_program *x)
{
	int	a;
	int	b;

	x->mlx.ptr = mlx_init();
	check_malloc(x, x->mlx.ptr);
	x->mlx.win = mlx_new_window(x->mlx.ptr, 1800, 1000, "cub3d");
	x->mlx.player = mlx_xpm_file_to_image(x->mlx.ptr, "bonus/red.xpm", &a, &b);
	x->mlx.wall = mlx_xpm_file_to_image(x->mlx.ptr, "bonus/gray.xpm", &a, &b);
	x->mlx.floor = mlx_xpm_file_to_image(x->mlx.ptr, "bonus/blue.xpm", &a, &b);
	x->mlx.mdoor = mlx_xpm_file_to_image(x->mlx.ptr, "bonus/brown.xpm", &a, &b);
	x->mlx.walls[0] = mlx_image_init(x->mlx.ptr, x->wall.no, &a, &b);
	x->mlx.walls[1] = mlx_image_init(x->mlx.ptr, x->wall.ea, &a, &b);
	x->mlx.walls[2] = mlx_image_init(x->mlx.ptr, x->wall.so, &a, &b);
	x->mlx.walls[3] = mlx_image_init(x->mlx.ptr, x->wall.we, &a, &b);
	mlx_animation_init(x->mlx.ptr, x->mlx.animation, &a, &b);
	check_malloc(x, x->mlx.animation);
	x->mlx.door = create_door_img(x, &a, &b, 0);
	x->mlx.screen = malloc(sizeof(t_mlx_image));
	check_malloc(x, x->mlx.screen);
	x->mlx.screen->img = mlx_new_image(x->mlx.ptr, 4000, 4000);
	if (!x->mlx.screen->img)
		return (special_free((void **)&x->mlx.screen),
			free_program(ALLOC_ERR, x, 1));
	x->mlx.screen->addr = mlx_get_data_addr(x->mlx.screen->img,
			&x->mlx.screen->bits_per_pixel, &x->mlx.screen->size_line, &b);
}

void	*mlx_image_init(void *xvar, char *file, int *width, int *height)
{
	t_mlx_image	*new;

	new = ft_calloc(1, sizeof(t_mlx_image));
	if (!new)
		return (NULL);
	new->img = mlx_xpm_file_to_image(xvar, file, width, height);
	if (!new->img)
		return (free(new), NULL);
	new->addr = mlx_get_data_addr(new->img, &new->bits_per_pixel,
			&new->size_line, height);
	return (new);
}

void	create_sky_and_floor(t_program *x)
{
	char	**rgb;

	if ((int)ft_nb_words(x->colors.c, ',', 1) != 3)
		free_program("Wrong rgb!!!", x, 1);
	rgb = ft_split(x->colors.c, ',');
	check_malloc(x, rgb);
	if (ft_atoi(rgb[0]) > 255 || ft_atoi(rgb[0]) < 0 || control_rgb(x, rgb[0]) \
	|| ft_atoi(rgb[1]) > 255 || ft_atoi(rgb[1]) < 0 || control_rgb(x, rgb[1]) \
	|| ft_atoi(rgb[2]) > 255 || ft_atoi(rgb[2]) < 0 || control_rgb(x, rgb[2]))
		return (free_string_array(rgb), free_program("Wrong rgb!!!", x, 1));
	x->colors.c_rpg = (ft_atoi(rgb[0]) << 16)
		+ (ft_atoi(rgb[1]) << 8) + ft_atoi(rgb[2]);
	free_string_array(rgb);
	if ((int)ft_nb_words(x->colors.f, ',', 1) != 3)
		free_program("Wrong rgb!!!", x, 1);
	rgb = ft_split(x->colors.f, ',');
	check_malloc(x, rgb);
	if (ft_atoi(rgb[0]) > 255 || ft_atoi(rgb[0]) < 0 || control_rgb(x, rgb[0]) \
	|| ft_atoi(rgb[1]) > 255 || ft_atoi(rgb[1]) < 0 || control_rgb(x, rgb[1]) \
	|| ft_atoi(rgb[2]) > 255 || ft_atoi(rgb[2]) < 0 || control_rgb(x, rgb[2]))
		return (free_string_array(rgb), free_program("Wrong rgb!!!", x, 1));
	x->colors.f_rpg = (ft_atoi(rgb[0]) << 16)
		+ (ft_atoi(rgb[1]) << 8) + ft_atoi(rgb[2]);
	return (free_string_array(rgb), x->list
		= ft_calloc(1, sizeof(t_linkedlist)), check_malloc(x, x->list));
}
