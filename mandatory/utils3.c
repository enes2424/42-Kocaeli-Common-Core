/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eates <eates@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 05:36:12 by eates             #+#    #+#             */
/*   Updated: 2024/01/28 20:43:50 by eates            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "../libft/libft.h"
#include "../minilibx/mlx.h"

void	init_program(t_program *x)
{
	int	a;
	int	b;

	x->mlx.ptr = mlx_init();
	check_malloc(x, x->mlx.ptr);
	x->mlx.win = mlx_new_window(x->mlx.ptr, 1800, 1000, "cub3d");
	x->mlx.walls[0] = mlx_image_init(x->mlx.ptr, x->wall.no, &a, &b);
	x->mlx.walls[1] = mlx_image_init(x->mlx.ptr, x->wall.ea, &a, &b);
	x->mlx.walls[2] = mlx_image_init(x->mlx.ptr, x->wall.so, &a, &b);
	x->mlx.walls[3] = mlx_image_init(x->mlx.ptr, x->wall.we, &a, &b);
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

void	render(t_program *x)
{
	mlx_clear_window(x->mlx.ptr, x->mlx.win);
	mlx_put_background(x);
	raycasting(x, 121.5 + x->angle, 0);
	mlx_put_image_to_window(x->mlx.ptr, x->mlx.win, x->mlx.screen->img, 0, 0);
	x->tmp = ft_itoa(x->speed * x->multipler);
	check_malloc(x, x->tmp);
	x->tmp = ft_strjoin(x->tmp, " pixel / step");
	check_malloc(x, x->tmp);
	mlx_string_put(x->mlx.ptr, x->mlx.win, 1650, 30, 0, x->tmp);
	special_free((void **)&x->tmp);
}

void	mlx_put_background(t_program *x)
{
	int	i;
	int	j;

	i = -1;
	while (++i < 1000)
	{
		j = -1;
		while (++j < 1800)
			*(unsigned int *)(x->mlx.screen->addr + i * x->mlx.screen->size_line
					+ 4 * j)
				= (i < 500) * x->colors.c_rpg + (i >= 500) * x->colors.f_rpg;
	}
}
