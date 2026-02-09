NAME			=	minishell

CC				=	gcc
CFLAGS			=	-Wall -Wextra -Werror -lreadline
RM				=	rm -rf

SRCS			=	minishell.c \
					free1.c \
					free2.c \
					env1.c \
					env2.c \
					env3.c \
					utils.c \
					special_expressions.c \
					cmd1.c \
					cmd2.c \
					path.c \
					heredoc.c \
					export.c \
					echo.c \
					signal.c \
					exit.c \
					cd.c \
					pwd.c \
					init.c \
					token_control.c \
					redirection.c \
					exec.c

BSRCS			=	bonus/minishell_bonus.c \
					bonus/free1_bonus.c \
					bonus/free2_bonus.c \
					bonus/env1_bonus.c \
					bonus/env2_bonus.c \
					bonus/env3_bonus.c \
					bonus/utils1_bonus.c \
					bonus/utils2_bonus.c \
					bonus/special_expressions_bonus.c \
					bonus/cmd1_bonus.c \
					bonus/cmd2_bonus.c \
					bonus/path_bonus.c \
					bonus/heredoc_bonus.c \
					bonus/export_bonus.c \
					bonus/echo_bonus.c \
					bonus/signal_bonus.c \
					bonus/exit_bonus.c \
					bonus/cd_bonus.c \
					bonus/pwd_bonus.c \
					bonus/init_bonus.c \
					bonus/token_control_bonus.c \
					bonus/redirection_bonus.c \
					bonus/exec_bonus.c \
					bonus/wilcard_bonus.c \
					bonus/control_bonus.c \
					bonus/clear_extra_parantheses_bonus.c

LIBFT_PATH		=	./libft
LIBFT			=	$(LIBFT_PATH)/libft.a

all:				libft $(NAME)

$(NAME):
					@$(CC) $(CFLAGS) -o $(NAME) $(SRCS) $(LIBFT)

bonus:				libft
					@$(CC) $(CFLAGS) -o $(NAME) $(BSRCS) $(LIBFT)

run:
	@make re
	@./minishell
	@make fclean

brun:
	@make bre
	@./minishell
	@make fclean

v:
	@make re
	@valgrind --leak-check=full ./minishell
	@make fclean

bv:
	@make bre
	@valgrind --leak-check=full ./minishell
	@make fclean

libft:
	@make -C $(LIBFT_PATH)

clean:
	@make -C $(LIBFT_PATH) clean
	@$(RM) minishell.dSYM

f:	fclean

fclean: clean
	@make -C $(LIBFT_PATH) fclean
	@$(RM) $(NAME)

n:
	norminette $(SRCS) minishell.h

bn:
	norminette $(BSRCS) minishell_bonus.h

re:					fclean all
bre:				fclean bonus

.PHONY:				all clean fclean re libft bonus
