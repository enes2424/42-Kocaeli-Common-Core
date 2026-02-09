NAME			=	cub3d
BONUS_NAME		=	cub3d_bonus

CC				=	gcc
CFLAGS			=	-Wall -Wextra -Werror -g
RM				=	rm -rf

ECHO			= echo

SRCDIR			= ./

MANDATORY_OBJ	= $(addprefix $(OBJDIR)/, $(notdir $(patsubst %.c, %.o, $(SRC_MANDATORY))))
BONUS_OBJ		= $(addprefix $(OBJDIR)/, $(notdir $(patsubst %.c, %.o, $(SRC_BONUS))))

OBJDIR		= ./obj

SRC_MANDATORY	=	mandatory/utils.c \
					mandatory/utils1.c \
					mandatory/utils2.c \
					mandatory/utils3.c \
					mandatory/utils4.c \
					mandatory/utils5.c \
					mandatory/utils6.c \
					mandatory/utils7.c \
					mandatory/utils8.c \
					mandatory/cub3d.c


SRC_BONUS		=	bonus/utils_bonus.c \
					bonus/utils1_bonus.c \
					bonus/utils2_bonus.c \
					bonus/utils3_bonus.c \
					bonus/utils4_bonus.c \
					bonus/utils5_bonus.c \
					bonus/utils6_bonus.c \
					bonus/utils7_bonus.c \
					bonus/utils8_bonus.c \
					bonus/utils9_bonus.c \
					bonus/utils10_bonus.c \
					bonus/cub3d_bonus.c

SRCDIR_MANDATORY =	mandatory
SRCDIR_BONUS	=	bonus

LIBFT_PATH		=	./libft
LIBFT			=	$(LIBFT_PATH)/libft.a

MINILIBX_PATH		=	./minilibx
MLXFLAG				= -framework OpenGL -framework AppKit -L$(MINILIBX_PATH) -lmlx

all: $(NAME)
a: all

$(NAME): $(LIBFT) $(MANDATORY_OBJ)
	@$(CC) $(CFLAGS) $(LIBFT) $(MLXFLAG) $(MANDATORY_OBJ) -o $(NAME)
	@$(ECHO) "\033[0;32m> cub3D Compiled\033[0m"

$(OBJDIR):
	@test -d $(OBJDIR) || mkdir $(OBJDIR)

$(OBJDIR)/%.o:: $(SRCDIR)/%.c | $(OBJDIR)
	@$(CC) $(INCLUDE) $(CFLAGS)  -c -o $@ $< \
	&& $(ECHO) "\033[1;30m[CC] : Compiled $(notdir $<) \
	[\033[0;32mOk\033[1;30m]\033[0m" \
	|| $(ECHO) "\033[1;30m[CC] : Compiled $(notdir $<) \
	[\033[0;7;31mError\033[0;1;30m]\033[0m"

$(OBJDIR)/%.o:: $(SRCDIR_MANDATORY)/%.c | $(OBJDIR)
	@$(CC) $(INCLUDE) $(CFLAGS)  -c -o $@ $< \
	&& $(ECHO) "\033[1;30m[CC] : Compiled $(notdir $<) \
	[\033[0;32mOk\033[1;30m]\033[0m" \
	|| $(ECHO) "\033[1;30m[CC] : Compiled $(notdir $<) \
	[\033[0;7;31mError\033[0;1;30m]\033[0m"

$(OBJDIR)/%.o:: $(SRCDIR_BONUS)/%.c | $(OBJDIR)
	@$(CC) $(INCLUDE) $(CFLAGS)  -c -o $@ $< \
	&& $(ECHO) "\033[1;30m[CC] : Compiled $(notdir $<) \
	[\033[0;32mOk\033[1;30m]\033[0m" \
	|| $(ECHO) "\033[1;30m[CC] : Compiled $(notdir $<) \
	[\033[0;7;31mError\033[0;1;30m]\033[0m"

b: bonus
bonus: $(BONUS_NAME)

$(BONUS_NAME): $(LIBFT) $(BONUS_OBJ)
	@$(CC) $(CFLAGS) $(LIBFT) $(MLXFLAG) $(BONUS_OBJ) -o $(BONUS_NAME)
	@$(ECHO) "\033[0;32m> cub3D_bonus Compiled\033[0m"

$(LIBFT):
	@make -C $(LIBFT_PATH) all

mlx:
	@make -C $(MINILIBX_PATH) all

c: clean
clean:
	@make -C $(LIBFT_PATH) clean
	@$(RM) $(OBJDIR)

f: fclean
fclean:	clean
	@make -C $(LIBFT_PATH) fclean
	@$(RM) $(NAME) $(BONUS_NAME)

r: re
re:	fclean all

br: bre
rb: bre
bre: fclean bonus

.PHONY:	all clean fclean re bre a b c f r br rb

