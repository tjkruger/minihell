NAME		=	minishell

# === Directories ===
SRC_DIR		=	src
LIBFT_DIR	=	libft
OBJ_DIR		=	obj
INC_DIR		=	include

# === Source groups ===
MAIN		=	main.c
HISTORY		=	history.c

TOKENS		=	tokens/token.c \
				tokens/token_utils.c

BUILDINS		=	buildins/echo.c

# Combine all source groups here
SRC			=	$(MAIN) $(HISTORY) $(TOKENS) $(BUILDINS)

# === Libft sources ===
SRCSLIBFT	=	ft_bzero.c \
				ft_isalnum.c \
				ft_isalpha.c \
				ft_isascii.c \
				ft_isdigit.c \
				ft_isprint.c \
				ft_memset.c \
				ft_strlen.c \
				ft_memcpy.c \
				ft_memmove.c \
				ft_strlcpy.c \
				ft_strlcat.c \
				ft_toupper.c \
				ft_tolower.c \
				ft_strchr.c \
				ft_strrchr.c \
				ft_strncmp.c \
				ft_memchr.c \
				ft_memcmp.c \
				ft_strnstr.c \
				ft_atoi.c \
				ft_calloc.c \
				ft_strdup.c \
				ft_substr.c \
				ft_strjoin.c \
				ft_strtrim.c \
				ft_split.c \
				ft_itoa.c \
				ft_strmapi.c \
				ft_striteri.c \
				ft_putchar_fd.c \
				ft_putstr_fd.c \
				ft_putendl_fd.c \
				ft_putnbr_fd.c

# === Object lists ===
OBJ			=	$(addprefix $(OBJ_DIR)/, $(SRC:.c=.o)) \
				$(addprefix $(OBJ_DIR)/, $(notdir $(SRCSLIBFT:.c=.o)))

# === Compiler flags ===
CC			=	cc
CFLAGS		=	-Wall -Werror -Wextra -I$(INC_DIR)
READLINE	=	-lreadline

# === Rules ===
all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) $(READLINE) -o $(NAME)
	@echo "✨ $(NAME) built successfully!"

# Rule to compile project .c files (handles subfolders!)
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

# Rule to compile libft .c files
$(OBJ_DIR)/%.o: $(LIBFT_DIR)/%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

run: $(NAME)
	./$(NAME)

clean:
	@rm -rf $(OBJ_DIR)
	@echo "🧹 Objects cleaned."

fclean: clean
	@rm -f $(NAME)
	@echo "💥 Full clean done."

re: fclean all

.PHONY: all clean fclean re
