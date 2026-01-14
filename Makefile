# === Project Name ===
NAME        = minishell

# === Directories ===
SRC_DIR     = src
OBJ_DIR     = obj
INC_DIR     = include
LIBFT_DIR   = libft

# === Source groups ===
MAIN        = main.c
HISTORY     = history.c
FREE        = all_free_functions.c

PARSER      = parser/create_command_list.c \
              parser/command_list_helper.c

LEXER = lexer/tokens.c \
        lexer/expansion.c \
        lexer/allocate-fill_pretoken.c \
        lexer/node_append_helper.c \
        lexer/string-argument_helper.c \
        lexer/token-pretoken_management.c \
        lexer/token-pretoken_management2.c \
		lexer/token-pretoken_management3.c \
        lexer/token_helpers-checks.c

BUILTINS    = builtins/echo.c \
					builtins/cd.c \
					builtins/export.c \
					builtins/pwd.c \
					builtins/unset.c \
					builtins/exit.c \
					builtins/env.c \
					signals/signals.c \

EXECUTION	= 		execution/pipes.c \
					execution/child.c \
					execution/fd.c \
					execution/heredoc.c \
					execution/handle_redir.c \
					execution/fork.c \
					execution/heredoc_utils.c \
					execution/execution.c \
					execution/redirections.c
		
TRASH		=		trash/trash.c \
					trash/gc_split.c \
					trash/gc_itoa.c 

UTILS		=		utils/utils_hkaraogl_2.c \
					utils/utils_hkaraogl_3.c \
					utils/utils_hkaraogl.c 
				
ENV			=		environment/environment_utils.c \
					environment/environment.c

INIT		=		init/init_environment.c \
					init/init.c 


# Combine all source groups
SRC         = $(MAIN) $(HISTORY) $(LEXER) $(BUILTINS) $(PARSER) $(EXECUTION) $(TRASH) $(UTILS) $(ENV) $(INIT) $(FREE)

# === Object list (preserve directories) ===
OBJ         = $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRC))

# === Compiler flags ===
CC          = cc 
CFLAGS = -g -I$(INC_DIR)
READLINE    = -lreadline

# === Default target ===
all: $(NAME)

# === Build minishell ===
$(NAME): $(OBJ)
	$(MAKE) -C $(LIBFT_DIR)        # build libft.a
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT_DIR)/libft.a $(READLINE) -o $(NAME)
	@echo "✨ $(NAME) built successfully!"

# === Pattern rule for all .c files ===
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# === Ensure object folder exists ===
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

# === Run ===
run: $(NAME)
	./$(NAME)

# === Clean ===
clean:
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean
	@echo "🧹 Objects cleaned."

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@echo "💥 Full clean done."

re: fclean all

.PHONY: all clean fclean re run
