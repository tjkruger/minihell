

#include "minishell.h"

t_one_command   create_new_command_node(void)
{
    t_one_command *new_command;

}

void    add_word_to_cmd(t_one_command *curr_cmd, char *value)
{

}

int is_redirection(t_token *token)
{
    if ((token->value[0] == '<' || token->value[0] == '>') && token->value[1] == '\0')
        return 1;

    if (ft_strncmp(token->value, "<<", 2) == 0 || ft_strncmp(token->value, ">>", 2) == 0)
        return 1;

    return 0;
}


void    add_file_to_cmd(t_one_command *curr_cmd, char *value)
{

}

void    add_cmd_to_list(t_all_commands *cmd_list, t_one_command *curr_cmd)
{

}

t_all_commands  build_commands(t_token *tokens)
{
    while (tokens)
    {
        t_one_command *curr_cmd = create_new_command_node();//initialize a new node for the big

        while (tokens && tokens->type != TOKEN_PIPE)
        {
            if (tokens->type == TOKEN_WORD)
                add_word_to_cmd(curr_cmd, tokens->value);//ez just append to list
            else if (is_redirection(tokens))//need the function for detection what symbol it is can use maybe same as for the |
            {
                tokens = tokens->next;
                add_file_to_cmd(curr_cmd, tokens->value, redir_type);// no fckn idea how to do it 
            }
            tokens = tokens->next;
        }

        add_cmd_to_list(cmd_list, curr_cmd);//how ? well see ig

        if (tokens && tokens->type == TOKEN_PIPE)
            tokens = tokens->next;
    }

}
// cmd type muss noch herausgefunden werden


void free_cmd_list(t_cmd_list *cmds)
{
    t_cmd_node *tmp;

    while (cmds && cmds->head)
    {
        tmp = cmds->head->next;

        if (cmds->head->cmd)
        {
            for (int i = 0; cmds->head->cmd[i]; i++)
                free(cmds->head->cmd[i]);
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
