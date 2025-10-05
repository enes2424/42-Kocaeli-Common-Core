NAME	= pipex

SRC		= pipex.c pipex_utils.c \
		  ft_split.c pipex_others.c

BSRC	= pipex_bonus.c pipex_utils_bonus.c \
		  ft_split_bonus.c pipex_others_bonus.c \
		  pipex_child_bonus.c \
		  getnextline/get_next_line.c \
		  getnextline/get_next_line_utils.c

OBJ		= $(SRC:.c=.o)
BOBJ	= $(BSRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) pipex.h
	cc -Wall -Wextra -Werror -o $(NAME) $(OBJ)

bonus: .bonus

.bonus: $(BOBJ) pipex_bonus.h getnextline/get_next_line.h
	cc -Wall -Wextra -Werror -o $(NAME) $(BOBJ)
	@touch .bonus

%.o: %.c
	cc -Wall -Wextra -Werror -c $< -o $@

clean:
	rm -rf $(OBJ) $(BOBJ)

fclean: clean
	rm -rf $(NAME) .bonus

re: fclean all

.PHONY: all clean fclean re bonus