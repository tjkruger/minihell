

#include "minishell.h"

t_one_command   *create_new_command_node(void)// initialize t_one_command
{
    t_one_command *new_command;
    new_command = malloc(sizeof(t_one_command));
    if (!new_command)
        return (NULL);
    new_command->cmd_type = 0;
    new_command->cmd = NULL;
    new_command->files = NULL;
    new_command->next = NULL;
    return(new_command);
}
// basically just fill the ** in t_one_command char **command
void    add_word_to_cmd(t_one_command *curr_cmd, char *value) 
{
    int i;
    int j;

    j = 0;
    i = 0;
    char **new_cmd;
    while(curr_cmd->cmd[i] != NULL)
        i++;
    new_cmd = malloc(sizeof(char *) * (i + 2));
    while(j < i)
        new_cmd[j] = curr_cmd[j];
    new_cmd[i] = ft_strdup(value);
    new_cmd[i + 1] = NULL;
}

void add_cmd_to_list(t_all_commands *cmd_list, t_one_command *curr_cmd)
{
    if (!cmd_list || !curr_cmd)
        return;
    curr_cmd->next = NULL;
    if (cmd_list->head == NULL)//first time filling the t_all_commands
    {
        cmd_list->head = curr_cmd;
        cmd_list->tail = curr_cmd;
    }
    else//every other case when head is already set
    {
        cmd_list->tail->next = curr_cmd;
        cmd_list->tail = curr_cmd;
    }
    cmd_list->size++;
}