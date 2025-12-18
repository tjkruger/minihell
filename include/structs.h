

#ifndef STRUCTS_H
# define STRUCTS_H

typedef enum CMD_TYPE
{
	CMD,
	BUILTIN,
}	t_CMD_TYPE;

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

typedef enum    e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,//<
	TOKEN_REDIR_OUT,//>
	TOKEN_REDIR_APPEND,//<<
	TOKEN_REDIR_HEREDOC,// >>
} t_token_type;

typedef struct s_env_node
{
	char *key;
	char *value;
	int exported;
	struct s_env_node	*next;
} t_env_node;

typedef	struct s_env_list// kommt mit rein
{
	t_env_node	*head;
	t_env_node	*tail;
	ssize_t	size;
	int	last_exit;
}	t_env_list;

typedef struct s_pipes// kommt mit rein
{
	int **pipes;
	pid_t *pids;
	int pipe_count;
	int command_count;
}	t_pipes;

typedef struct s_file_node
{
	char *filename;
	char *delimiter;
	int	qoutes_in_heredoc;
	int redir_type;
	struct s_file_node *next;
} t_file_node;

typedef struct s_file_list// kommt mit rein
{
	t_file_node *head;
	t_file_node *tail;
	ssize_t size;
} t_file_list;

typedef struct s_token// kommt mit rein
{
	char            *value;
	char            *dna;
	t_token_type    type;
	struct  s_token *next;
}   t_token;

//muss executer uebernehemen (t_command_node)
typedef struct s_one_command
{
	struct s_one_command *next;
	int cmd_type;// 1 for buildin, 0 for external
	int executable;// 1 if executable, 0 if not
	char **cmd;
	t_file_list *files;
} t_one_command;

//muss executer uebernehemen (t_command_list)
typedef struct s_all_commands// kommt mit rein
{
	int syntax_error;
	t_one_command *head;
	t_one_command *tail;
	ssize_t size;
} t_all_commands;

typedef struct s_history// kommt mit rein
{
	char                *command;
	struct s_history    *next;
} t_history;

typedef struct s_pretoken// kommt mit rein
{
	char    **token;
	char    **dna;
} t_pretoken;

typedef struct s_trash_node
{
	void *data;
	struct s_trash_node *next;
} t_trash_node;

typedef struct s_trash// kommt mit rein
{
	struct s_trash_node *head;
	struct s_trash_node *tail;
	ssize_t size;
} t_trash;
//typedef t_pretoken *t_pretoken_pointer;

#endif