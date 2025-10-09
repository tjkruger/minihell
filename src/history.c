
#include "minishell.h"


void    my_history(char **args, t_shell  *history)
{
    (void)args;
    t_myhistory *current = history->head;
    while (current)
    {
        printf("%s\n", current->command);
        current = current->next;
    }
}

t_myhistory *create_history_node(const char *input)
{
    t_myhistory *new_node = malloc(sizeof(t_myhistory));
    if (!new_node)
        return NULL;
    new_node->command = strdup(input);
    new_node->next = NULL;
    new_node->prev = NULL;
    return new_node;
}

void    add_to_history(char *input, t_myhistory **head, t_myhistory **tail)
{
    t_myhistory *new_node = create_history_node(input);
    if (!new_node)
        return;
     if (*head == NULL)
    {
        *head = new_node;
        *tail = new_node;
    }
    else
    {
        new_node->prev = *tail;
        (*tail)->next = new_node;
        *tail = new_node;
    }

}

void    initialize_history_list(t_myhistory *list)
{
    list->command = NULL;
    list->next = NULL;
    list->prev = NULL;
}

void    free_myhistory(t_myhistory *head)
{
    if(!head)
        return;

    free_myhistory(head->next);
    free(head->command);
    free(head);
}