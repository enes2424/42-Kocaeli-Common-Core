SRCS	= philo1.c philo2.c philo3.c main.c u_int64_atoi.c

CC = gcc
RM = rm -f
FLAGS = -Wall -Wextra -Werror #-pthread -fsanitize=thread -g
NAME = philo

all : $(NAME)

$(NAME) :
		$(CC) $(FLAGS) -o $(NAME) $(SRCS)

clean :
	$(RM) $(NAME)

fclean : clean

re : fclean $(NAME)

.PHONY : all clean fclean re
