

#include "minishell.h"

t_file_list *init_file_list(void)
{
    t_file_list *list = malloc(sizeof(t_file_list));
    if (!list)
        return NULL;
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    return list;
}

t_file_node *create_file_node(char *value, enum redir_type)
{
    t_file_node *node = malloc(sizeof(t_file_node));
    if (!node)
        return NULL;
    node->filename = ft_strdup(value);
    node->redir_type = redir_type;
    node->next = NULL;
    return node;
}

void add_file_to_cmd(t_one_command *curr_cmd, char *value, int redir_type)
{
    if (!curr_cmd || !value)
        return;

    if (!curr_cmd->files)
        curr_cmd->files = init_file_list();

    t_file_node *new_file = create_file_node(value, redir_type);
    if (!new_file)
        return;

    if (curr_cmd->files->head == NULL)
        curr_cmd->files->head = curr_cmd->files->tail = new_file;
    else
    {
        curr_cmd->files->tail->next = new_file;
        curr_cmd->files->tail = new_file;
    }
    curr_cmd->files->size++;
}


int find_cmd_type(char *cmd)
{
    (void) cmd;
    //bunch of else if statements with strcmp or so ...
    //bis zum ersten ' ' suchen und dann den command comparen zu den buildins no ?
    //also 1 for buildin and 0 for external ?
}

t_all_commands  *build_commands(t_token *tokens)
{
    while (tokens)
    {
        t_one_command *curr_cmd = create_new_command_node();

        while (tokens && tokens->type != TOKEN_PIPE)
        {
            if (tokens->type == TOKEN_WORD)
                add_word_to_cmd(curr_cmd, tokens->value);
            else if (tokens->type == TOKEN_REDIRECT_IN
                    || tokens->type == TOKEN_REDIRECT_OUT
                    || tokens->type == TOKEN_APPEND
                    || tokens->type == TOKEN_HEREDOC)
            {
                add_file_to_cmd(curr_cmd, tokens->next->value, tokens->type);
                tokens = tokens->next;
            }
            tokens = tokens->next;
        }
        curr_cmd->cmd_type = find_cmd_type(curr_cmd->cmd);//1 oder 0 zurueck depending on buildin or not
        add_cmd_to_list(cmd_list, curr_cmd);

        if (tokens && tokens->type == TOKEN_PIPE)
            tokens = tokens->next;
    }
    return(curr_cmd);
}


