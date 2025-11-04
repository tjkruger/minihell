#ifndef MINISHELL_H
# define MINISHELL_H

# include <ctype.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>


// all other .h files



# define PATH_MAX 4096

typedef struct s_file_node
{
	char				*filename;
	int					redir_type;
	struct s_file_node	*next;
}						t_file_node;


typedef struct s_file_list
{
	t_file_node			*head;
	t_file_node			*tail;
	ssize_t				size;
}						t_file_list;


typedef struct s_cmd_node
{
	int					cmd_type;
	char				**cmd;
	t_file_list			*files;
	struct s_cmd_node	*next;
}						t_cmd_node;


typedef struct s_cmd_list
{
	t_cmd_node			*head;
	t_cmd_node			*tail;
	ssize_t				size;
}						t_cmd_list;


typedef struct s_env_node
{
	char *key;
	char *value;
	struct s_env_node	*next;
} t_env_node;

typedef	struct s_env_list
{
	t_env_node	*head;
	t_env_node	*tail;
	ssize_t	size;
}	t_env_list;

# include "history.h"
# include "libft.h"
# include "tokens.h"
# include "utils.h"
# include "environment.h"
# include "buildins.h"

#endif