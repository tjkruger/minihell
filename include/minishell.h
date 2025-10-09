#ifndef MINISHELL_H
# define MINISHELL_H



#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
# include <readline/history.h>
# include <readline/readline.h>


typedef struct s_myhistory
{
    char *command;
    struct s_myhistory *next;
    struct s_myhistory *prev;
}   t_myhistory;

typedef struct s_shell
{
    t_myhistory *head;
    t_myhistory *tail;
}   t_shell;


typedef struct s_mycommands
{
    char *name;
    void (*func)(char **args, t_shell *shell);
}   t_mycommands;





void    my_history(char **args, t_shell  *history);
void    add_to_history(char *input, t_myhistory **head, t_myhistory **tail);
void    free_myhistory(t_myhistory *head);

#endif