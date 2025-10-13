NAME			=	so_long

CC				=	cc
CFLAGS			=	-Wall -Wextra -Werror
AR				=	ar
ARFLAGS 		=	rcs
RM				=	rm -rf

SRC				=	so_long.c so_long_other.c so_long_other2.c so_long_other3.c  so_long_other4.c main.c

BSRC			=	bonus/so_long_bonus.c bonus/so_long_other_bonus.c bonus/so_long_other2_bonus.c bonus/so_long_other3_bonus.c  bonus/so_long_other4_bonus.c bonus/main_bonus.c

LIBFT_PATH		=	./libft
LIBFT			=	$(LIBFT_PATH)/libft.a

MINILIBX_PATH		=	./minilibx

all:				$(NAME)

$(NAME):			$(LIBFT) mlx
					$(CC) $(CFLAGS) -o $(NAME) $(SRC) $(LIBFT) -framework OpenGL -framework AppKit -L$(MINILIBX_PATH) -lmlx

$(LIBFT):
					make -C $(LIBFT_PATH) all

bonus:				$(LIBFT) mlx
					$(CC) $(CFLAGS) -o $(NAME) $(BSRC) $(LIBFT) -framework OpenGL -framework AppKit -L$(MINILIBX_PATH) -lmlx

mlx:
					make -C $(MINILIBX_PATH) all

clean:
					make -C $(LIBFT_PATH) clean
					make -C $(MINILIBX_PATH) clean

fclean:				clean
					make -C $(LIBFT_PATH) fclean
					$(RM) $(NAME)

re:					fclean all

bonusre:			fclean bonus

.PHONY:				all clean fclean re libft bonus
