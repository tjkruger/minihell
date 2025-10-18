#ifndef HISTORY_H
# define HISTORY_H

typedef struct s_history
{
    char                *command;
    struct s_history    *next;
} t_history;

int is_empty_or_whitespace(const char *s);
t_history *add_to_hist_list(t_history **list, char *command_to_list);
void print_history(t_history *list);
void free_hist(t_history *history_list);

#endif

