/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_command_list.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjkruger <tjkruger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/12/17 15:35:27 by tjkruger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



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

t_file_node *create_file_node(char *value, char *dna, t_token_type redir_type)
{
    // t_file_node *node = (t_file_node *)ft_malloc(sizeof(t_file_node), 1);
    t_file_node *node = malloc(sizeof(t_file_node));
    if (!node)
        return NULL;
    node->qoutes_in_heredoc = 0;
    if(redir_type == TOKEN_REDIR_HEREDOC)
    {
        node->filename = NULL;
        node->delimiter = ft_strdup(value);
        if(ft_strchr(dna, 'D') || ft_strchr(dna, 'S'))
            node->qoutes_in_heredoc = 1;
    }
    else
    {
        node->filename = ft_strdup(value);
        node->delimiter = NULL;
    }
    node->redir_type = redir_type;  // store enum value
    node->next = NULL;
    return node;
}


void add_file_to_cmd(t_one_command *curr_cmd, char *value, int redir_type, char *dna)
{
    if (!curr_cmd || !value)
        return;

    if (!curr_cmd->files)
        curr_cmd->files = init_file_list();

    t_file_node *new_file = create_file_node(value, dna, redir_type);
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


int find_cmd_type(char **cmd)
{
    if (!cmd)
        return 0;
    
    if (ft_strcmp(cmd[0], "echo") == 0)
        return 1;
    if (ft_strcmp(cmd[0], "cd") == 0)
        return 1;
    if (ft_strcmp(cmd[0], "pwd") == 0)
        return 1;
    if (ft_strcmp(cmd[0], "export") == 0)
        return 1;
    if (ft_strcmp(cmd[0], "unset") == 0)
        return 1;
    if (ft_strcmp(cmd[0], "env") == 0)
        return 1;
    if (ft_strcmp(cmd[0], "exit") == 0)
        return 1;
    
    return 0;
}

int find_executable(char *str)
{
    int i;

    i = 0;
    if(str[i] == '.')
        if(str[++i] == '/')
            return (1);
    return(0);
}

t_all_commands *create_new_commands_list(void)
{
    t_all_commands *list = malloc(sizeof(t_all_commands));
    if (!list)
        return NULL;
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    list->syntax_error = 0;
    return list;
}


t_all_commands *build_commands(t_token *tokens)
{
    t_all_commands *cmd_list = create_new_commands_list(); // function to init head/tail
    while (tokens)
    {
        t_one_command *curr_cmd = create_new_command_node();

        while (tokens && tokens->type != TOKEN_PIPE)
        {

            if (tokens->type == TOKEN_WORD)
                add_word_to_cmd(curr_cmd, tokens->value);


            else if (tokens->type == TOKEN_REDIR_IN
                     || tokens->type == TOKEN_REDIR_OUT
                     || tokens->type == TOKEN_REDIR_APPEND
                     || tokens->type == TOKEN_REDIR_HEREDOC)
            {
                if(tokens->next == NULL || tokens->next->type != TOKEN_WORD) 
                    return(NULL);
                add_file_to_cmd(curr_cmd, tokens->next->value, tokens->type, tokens->next->dna);
                tokens = tokens->next; // skip filename
            }
            tokens = tokens->next;
        }
        if (curr_cmd->cmd == NULL && curr_cmd->files == NULL)
            return NULL;
        if(curr_cmd->cmd)
        {
            curr_cmd->cmd_type = find_cmd_type(curr_cmd->cmd); // determine buildin or not
            curr_cmd->executable = find_executable(curr_cmd->cmd[0]);//make executable flag maybe put somewhere else but later in cleanup part no ?
        }
        add_cmd_to_list(cmd_list, curr_cmd);
        if (tokens && tokens->type == TOKEN_PIPE)
            tokens = tokens->next;
    }

    return cmd_list;
}
