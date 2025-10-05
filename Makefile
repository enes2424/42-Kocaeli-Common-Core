NAME = libftprintf.a

SRC =	ft_printf.c \
		writestring.c \
		writenumber.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)

$(OBJ): ft_printf.h

%.o: %.c
	cc -Wall -Wextra -Werror -c $< -o $@

clean:
	rm -rf $(OBJ)

fclean : clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
