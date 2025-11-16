
// #include <ctype.h>
#include "minishell.h"

int is_empty_or_whitespace(const char *s)
{
    if (!s) 
        return 1;
    while (*s)
    {
        if (!isspace((unsigned char)*s)) 
            return 0;
        s++;
    }
    return 1;
}

t_history *add_to_hist_list(t_history **list, char *command_to_list)
{
    t_history *entry = malloc(sizeof(t_history));
    if (!entry)
        return NULL;

    entry->command = strdup(command_to_list);  // duplicate the string safely
    entry->next = NULL;

    if (*list == NULL)
        *list = entry;  // first node
    else
    {
        t_history *tmp = *list;
        while (tmp->next)
            tmp = tmp->next;
        tmp->next = entry;
    }
    return entry;
}

void print_history(t_history *list)
{
    int i = 1;
    while (list)
    {
        printf("%d  %s\n", i, list->command);
        list = list->next;
        i++;
    }
}


