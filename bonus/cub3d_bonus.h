/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eates <eates@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 14:00:51 by eates             #+#    #+#             */
/*   Updated: 2024/01/28 21:05:24 by eates            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H
# define W		13
# define S		1
# define A		0
# define D		2
# define L		123
# define R		124
# define UP		126
# define DOWN	125
# define SHIFT	257
# define SPACE	49
# define B		11
# define ESC	53
# define PIXEL	150
# define PIXEL2	30
# define PI		3.14159265358979323846264338327950288
# define ALLOC_ERR "Couldn't take space with malloc!!!"

typedef struct s_map
{
	char	**map;
	char	**cropped_map;
	char	**copy;
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

typedef struct s_door
{
	int				x;
	int				y;
	int				is_open;
	struct s_door	*next;
}	t_door;

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
	void		*player;
	void		*wall;
	void		*floor;
	void		*mdoor;
	t_mlx_image	*door;
	t_mlx_image	*animation[12];
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
	t_door			*doors;
	t_mlx			mlx;
	t_mlx_image		*tmp_img;
	double			px[2];
	double			py[2];
	char			*tmp;
	char			*door;
	int				angle;
	int				speed;
	int				multipler;
	int				start;
	int				is_door;
	int				which_wall;
	int				mouse_x;
	int				mouse_y;
}	t_program;

void			check_arg(int ac, char **av);
void			init(t_program *x);
void			init_mlx(t_program *x);
void			create_map(t_program *x, int fd);
int				character_control(t_program *x, int is_there_player,
					int i, int j);
char			*control(t_program *x);
char			*control2(t_program *x, char *str);
char			*equalize(char *str, char **str2, t_program *x);
void			check_map(t_program *x);
void			check_map_and_changed(t_program *x);
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
void			render_continue(t_program *x, int mx, int my, int i);
void			render_continue_continue(t_program *x, int mx, int my);
int				exit_x(t_program *x);
int				handle(int key, t_program *x);
int				handle2(t_program *x);
int				release(int key, t_program *x);
void			close_map_control(t_program *x, int i, int j);
void			free_program(char *str, t_program *x, int status);
void			mlx_destroy(t_program *x);
void			mlx_image_destroy(void *ptr, t_mlx_image *image);
void			linkedlistclear(t_linkedlist *lst);
void			doorlistclear(t_door *lst);
void			special_free(void	**var);
void			check_malloc(t_program *x, void *value);
void			add_door(t_program *x, int dx, int dy);
t_door			*search(t_door *lst, int x, int y);
t_mlx_image		*create_door_img(t_program *x, int *a, int *b, int status);
int				handle_mouse_move(int mx, int my, t_program *x);
void			open_door(t_program *x);
int				control_rgb(t_program *x, char *str);

#endif
