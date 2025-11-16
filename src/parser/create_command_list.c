

#include "minishell.h"

int is_redirection(t_token *token)// find the special symbols
{
    if ((token->value[0] == '<' || token->value[0] == '>') && token->value[1] == '\0')
        return 1;

    if (ft_strncmp(token->value, "<<", 2) == 0 || ft_strncmp(token->value, ">>", 2) == 0)
        return 1;

    return 0;
}

t_file_list init_file_list(void)
{
    t_file_list *list = malloc(sizeof(t_file_list));
    if (!list)
        return NULL;
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    return list;
}

t_file_node create_file_node(char *value, enum redir_type)
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


t_all_commands  build_commands(t_token *tokens)
{
    while (tokens)
    {
        t_one_command *curr_cmd = create_new_command_node();

        while (tokens && tokens->type != TOKEN_PIPE)
        {
            if (tokens->type == TOKEN_WORD)
                add_word_to_cmd(curr_cmd, tokens->value);
            else if (is_redirection(tokens))
            {
                tokens = tokens->next;
                add_file_to_cmd(curr_cmd, tokens->value, redir_type); 
            }
            tokens = tokens->next;
        }

        add_cmd_to_list(cmd_list, curr_cmd);

        if (tokens && tokens->type == TOKEN_PIPE)
            tokens = tokens->next;
    }
}
// cmd type muss noch herausgefunden werden

