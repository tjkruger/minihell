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
#include <fcntl.h>


// all other .h files
struct s_file_list;
struct s_file_list;
struct s_cmd_node;
struct s_file_node;

int	execute_commands(t_cmd_list *cmd_lst, t_env_list *env_lst);
int set_redirections(t_file_list *files);


# define PATH_MAX 4096

typedef enum e_error
{
	ERR_CMD_NOT_FOUND = 127,
	ERR_PERM_DENIED = 126,
	ERR_EXEC_FAIL = 126,
	ERR_FORK = 1,
	ERR_PIPE = 1,
	ERR_MALLOC = 1,
	ERR_SYNTAX = 258,
}	t_error;


typedef enum CMD_TYPE
{
	BUILTIN,
	CMD,
}	t_CMD_TYPE;

typedef enum REDIR_TYPE
{
	REDIR_INPUT,
	REDIR_OUTPUT,
	REDIR_APPEND,
	REDIR_HEREDOC,
}	t_REDIR_TYPE;

typedef struct s_pipes
{
	int **pipes;
	pid_t *pids;
	int pipe_count;
	int command_count;
}	t_pipes;

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
# include "builtins.h"

#endif