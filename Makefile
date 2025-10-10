NAME			=	push_swap.a
NAME2			=	push_swap
NAME3			=	checker
NAME4			=	push_swap.c
NAME5			=	checker.c

CC				=	cc
CFLAGS			=	-Wall -Wextra -Werror
AR				=	ar
ARFLAGS 		=	rcs
RM				=	rm -rf

SRC				=	stack_operations.c \
					functions.c \
					other_functions.c \
					other_other_functions.c \
					sort.c \
					sort2.c \
					ft_atoi.c

OBJ_DIR			=	obj
OBJS			=	$(SRC:%.c=$(OBJ_DIR)/%.o)

LIBFT_PATH		=	./libft
LIBFT			=	$(LIBFT_PATH)/libft.a

$(OBJ_DIR)/%.o:		%.c
					$(CC) $(CFLAGS) -c $< -o $@

all:				$(NAME)

$(NAME):			push_swap.h $(LIBFT) $(OBJ_DIR) $(OBJS)
					cp	$(LIBFT) $(NAME)
					$(AR) $(ARFLAGS) $(NAME) $(OBJS)
					$(CC) $(CFLAGS) -o $(NAME2) $(NAME4) $(NAME)
					$(CC) $(CFLAGS) -o $(NAME3) $(NAME5) $(NAME)

$(LIBFT):
					make -C $(LIBFT_PATH) all

$(OBJ_DIR):
					mkdir -p $(OBJ_DIR)

clean:
					make -C $(LIBFT_PATH) clean
					$(RM) $(OBJ_DIR) $(NAME)

fclean:				clean
					make -C $(LIBFT_PATH) fclean
					$(RM) $(NAME2) $(NAME3)

re:					fclean all

.PHONY:				all clean fclean re
