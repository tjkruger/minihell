#include "minishell.h"

t_one_command   *create_new_command_node(t_trash *trash)// initialize t_one_command
{
    t_one_command *new_command;
    new_command = gc_malloc(trash, 1, sizeof(t_one_command));
    if (!new_command)
        return (NULL);
    new_command->cmd_type = 0;
    new_command->executable = 0;
    new_command->cmd = NULL;
    new_command->files = NULL;
    new_command->next = NULL;
    return(new_command);
}
// basically just fill the ** in t_one_command char **command
void add_word_to_cmd(t_one_command *curr_cmd, char *value, t_trash *trash) 
{
    int i = 0;
    int j = 0;
    char **new_cmd;
    
    if (curr_cmd->cmd)
    {
        while (curr_cmd->cmd[i] != NULL)
            i++;
    }
    new_cmd = gc_malloc(trash, (i + 2), sizeof(char *));
    if (!new_cmd)
        return;

    while (j < i)
    {
        new_cmd[j] = curr_cmd->cmd[j];
        j++;
    }

    new_cmd[i] = gc_strdup(trash, value);
    new_cmd[i + 1] = NULL;

    /* Do not free curr_cmd->cmd: GC manages memory now */
    curr_cmd->cmd = new_cmd;
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