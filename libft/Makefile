SRCS	=	*.c getnextline/*.c

CC = gcc
RM = rm -f
FLAGS = -Wall -Wextra -Werror
NAME = libft.a

all : $(NAME)

$(NAME) :
		@$(CC) $(FLAGS) -c $(SRCS)
		@ar rcs $(NAME) *.o

%.o : %.c
	@$(CC) -c $^

clean :
	@$(RM) *.o

fclean : clean
	@$(RM) $(NAME)

re : fclean $(NAME)

.PHONY : all clean fclean re
