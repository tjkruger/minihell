

NAME		=	minishell

SRC_DIR		=	src
LIBFT_DIR	=	libft
OBJ_DIR		=	obj
INC_DIR		=	include

SRC			=	main.c \
				
LIBFT		=	$(wildcard libft/*.c)
OBJ 		= 	$(addprefix $(OBJ_DIR)/, $(SRC:.c=.o)) $(addprefix $(OBJ_DIR)/, $(notdir $(LIBFT:.c=.o)))

cc			=	cc
CFLAGS		=	-Wall -Werror -Wextra -I$(INC_DIR)
READLINE	=	-lreadline




all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) $(READLINE) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(LIBFT_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re