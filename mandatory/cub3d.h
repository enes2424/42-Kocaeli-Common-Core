/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eates <eates@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 14:00:51 by eates             #+#    #+#             */
/*   Updated: 2024/01/28 20:40:48 by eates            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# define W		13
# define S		1
# define A		0
# define D		2
# define L		123
# define R		124
# define UP		126
# define DOWN	125
# define SHIFT	257
# define B		11
# define ESC	53
# define PIXEL	150
# define PIXEL2	30
# define PI		3.14159265358979323846264338327950288
# define ALLOC_ERR "Couldn't take space with malloc!!!"

typedef struct s_map
{
	char	**map;
	int		height;
	int		width;
}	t_map;

typedef struct s_wall
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
}	t_wall;

typedef struct s_colors
{
	char	*f;
	int		f_rpg;
	char	*c;
	int		c_rpg;
}	t_colors;

typedef struct s_player
{
	int		x;
	int		y;
	int		new_x;
	int		new_y;
	int		keys[6];
}	t_player;

typedef struct s_mlx_image
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		size_line;
}			t_mlx_image;

typedef struct s_mlx
{
	void		*ptr;
	void		*win;
	t_mlx_image	*screen;
	t_mlx_image	*walls[4];
}	t_mlx;

typedef struct s_linkedlist
{
	int					data;
	struct s_linkedlist	*next;
}	t_linkedlist;

typedef struct s_program
{
	t_linkedlist	*list;
	t_map			map;
	t_wall			wall;
	t_colors		colors;
	t_player		player;
	t_mlx			mlx;
	t_mlx_image		*tmp_img;
	double			px[2];
	double			py[2];
	char			*tmp;
	int				angle;
	int				speed;
	int				multipler;
	int				start;
	int				which_wall;
}	t_program;

void			check_arg(int ac, char **av);
void			init(t_program *x);
void			init_mlx(t_program *x);
void			create_map(t_program *x, int fd);
int				character_control(t_program *x);
char			*control(t_program *x);
char			*control2(t_program *x, char *str);
char			*equalize(char *str, char **str2, t_program *x);
void			path_finder(t_program *x, char **map, int i, int j);
char			**re_create(char **map, char **copy_map);
int				control3(char *str);
int				control4(char **map, int x);
void			play_program(t_program *x);
void			init_program(t_program *x);
void			*mlx_image_init(void *xvar, char *file,
					int *width, int *height);
void			create_sky_and_floor(t_program *x);
void			render(t_program *x);
void			mlx_put_background(t_program *x);
void			raycasting(t_program *x, double i, int j);
void			throwing_ray(t_program *x, double angle, double tanjant);
int				throwing_straight_ray(t_program *x, double px,
					double py, int tmp);
void			throwing_not_straight_ray(t_program *x,
					double *different, int *a);
int				throwing_ray1(t_program *x, double *different, int *a);
int				throwing_ray2(t_program *x, double *different, int *a);
void			put_image(t_program *x, int size, int j, int start);
int				exe(t_program *x, int a, int b, int c);
t_linkedlist	*add_node(t_program *x, t_linkedlist *list, int value);
int				exe2(t_program *x, t_linkedlist *list, int *arr);
void			put_image2(t_program *x, int size, int j, int start);
int				exit_x(t_program *x);
int				handle(int key, t_program *x);
int				handle2(t_program *x);
int				release(int key, t_program *x);
int				control_rgb(t_program *x, char *str);
void			free_program(char *str, t_program *x, int status);
void			mlx_destroy(t_program *x);
void			mlx_image_destroy(void *ptr, t_mlx_image *image);
void			linkedlistclear(t_linkedlist *lst);
void			special_free(void	**var);
void			check_malloc(t_program *x, void *value);

#endif
