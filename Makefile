NAME = libftprintf.a

SRC =	ft_printf.c \
		write_string.c \
		write_number.c

BSRC =	bonus/ft_printf_bonus.c \
		bonus/utils_bonus.c \
		bonus/write_char_bonus.c \
		bonus/write_string_bonus.c \
		bonus/write_pointer_bonus.c \
		bonus/write_int_bonus.c \
		bonus/write_uint_bonus.c \
		bonus/write_hex_bonus.c

OBJ = $(SRC:.c=.o)
BOBJ = $(BSRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) ft_printf.h
	ar rc $(NAME) $(OBJ)

bonus: $(BOBJ) bonus/ft_printf_bonus.h
	ar rc $(NAME) $(BOBJ)

%.o: %.c
	cc -Wall -Wextra -Werror -fPIC -c $< -o $@

clean:
	rm -rf $(OBJ) $(BOBJ)

fclean : clean
	rm -rf $(NAME)

re: fclean all

bonusre: fclean bonus

.PHONY: all bonus clean fclean re bonusre
