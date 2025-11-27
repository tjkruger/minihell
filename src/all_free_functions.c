#include "minishell.h"


void free_cmd_list(t_all_commands *cmds)
{
    t_one_command *tmp;
    if(!cmds)
        return;
    while (cmds && cmds->head)
    {
        tmp = cmds->head->next;

        if (cmds->head->cmd)
        {
            for (int i = 0; cmds->head->cmd[i]; i++)
            {
                free(cmds->head->cmd[i]);
            }
            free(cmds->head->cmd);
        }

        free_file_list(cmds->head->files);
        free(cmds->head);
        cmds->head = tmp;
    }
    free(cmds);
}


void free_file_list(t_file_list *files)
{
    t_file_node *tmp;

    while (files && files->head)
    {
        tmp = files->head->next;
        free(files->head->filename);
        free(files->head);
        files->head = tmp;
    }
    free(files);
}


void free_token_list(t_token *head)
{
    t_token *tmp;
    if (!head)
        return;
    while (head)
    {
        tmp = head->next;
        free(head->value);
        free(head);
        head = tmp;
    }
}


void free_hist(t_history *history_list)
{
    t_history *tmp;

    while (history_list)
    {
        tmp = history_list->next;
        free(history_list->command);
        free(history_list);
        history_list = tmp;
    }
    //rl_clear_history();// tf is this here ?
}

void free_pretoken(t_pretoken *pt)
{
    int i = 0;

    if (!pt)
        return;

    if (pt->token)
    {
        while (pt->token[i])
        {
            free(pt->token[i]);
            i++;
        }
        free(pt->token);
    }

    i = 0;
    if (pt->dna)
    {
        while (pt->dna[i])
        {
            free(pt->dna[i]);
            i++;
        }
        free(pt->dna);
    }

    free(pt);
}
