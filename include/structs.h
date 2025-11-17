

#ifndef STRUCTS_H
# define STRUCTS_H

typedef enum    e_token_type
{
    TOKEN_WORD,
    TOKEN_PIPE,
    TOKEN_REDIR_IN,//<
    TOKEN_REDIR_OUT,//>
    TOKEN_REDIR_APPEND,//<<
    TOKEN_REDIR_HEREDOC,// >> heredoc
} t_token_type;

typedef struct s_file_node 
{
    char *filename;
    int redir_type;
    struct s_file_node *next;
} t_file_node;

typedef struct s_file_list
{
    t_file_node *head;
    t_file_node *tail;
    ssize_t size;
} t_file_list;

typedef struct s_token
{
    char            *value;
    t_token_type    type;
    struct  s_token *next;
}   t_token;

typedef struct s_one_command
{
    struct s_one_command *next;
    int cmd_type;// 1 for buildin, 0 for external
    char **cmd;
    t_file_list *files;
} t_one_command;

typedef struct s_all_commands
{
    int syntax_error;
    t_one_command *head;
    t_one_command *tail;
    ssize_t size;
} t_all_commands;

typedef struct s_history
{
    char                *command;
    struct s_history    *next;
} t_history;


#endif