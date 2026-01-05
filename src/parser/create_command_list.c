/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_command_list.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaraogl <hkaraogl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2026/01/05 15:52:11 by hkaraogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "minishell.h"

t_file_list *init_file_list(t_ms *ms)
{
    t_file_list *list = gc_malloc(&ms->trash, 1, sizeof(t_file_list));
    if (!list)
        return NULL;
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    return list;
}

t_file_node *create_file_node(t_ms *ms, char *value, char *dna, t_token_type redir_type)
{
    t_file_node *node = gc_malloc(&ms->trash, 1, sizeof(t_file_node));
    if (!node)
        return NULL;
    node->qoutes_in_heredoc = 0;
    if(redir_type == TOKEN_REDIR_HEREDOC)
    {
        node->filename = NULL;
        node->delimiter = gc_strdup(&ms->trash, value);
        if (dna && (ft_strchr(dna, 'D') || ft_strchr(dna, 'S')))
            node->qoutes_in_heredoc = 1;
    }
    else
    {
        node->filename = gc_strdup(&ms->trash, value);
        node->delimiter = NULL;
    }
    node->redir_type = redir_type;  // store enum value
    node->next = NULL;
    return node;
}

static void ensure_file_list(t_ms *ms)
{
    if (!ms || !ms->curr_cmd)
        return;

    if (!ms->curr_cmd->files)
        ms->curr_cmd->files = init_file_list(ms);
}

static void append_file_node(t_ms *ms, t_file_node *node)
{
    t_file_list *files;

    if (!ms || !ms->curr_cmd || !node)
        return;

    files = ms->curr_cmd->files;
    if (!files->head)
        files->head = files->tail = node;
    else
    {
        files->tail->next = node;
        files->tail = node;
    }
    files->size++;
}


void add_file_to_cmd(t_ms *ms, char *value, int redir_type, char *dna)
{
    t_file_node *new_file;

    if (!ms || !value || !ms->curr_cmd)
        return;

    ensure_file_list(ms);

    new_file = create_file_node(ms, value, dna, redir_type);
    if (!new_file)
        return;

    append_file_node(ms, new_file);
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

t_all_commands *create_new_commands_list(t_trash *trash)
{
    t_all_commands *list = gc_malloc(trash, 1, sizeof(t_all_commands));
    if (!list)
        return NULL;
    list = NULL;
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    list->syntax_error = 0;
    return list;
}
 
 

t_all_commands *build_commands(t_ms *ms)
{
    t_all_commands *cmd_list;

    if (!ms)
        return NULL;

    cmd_list = create_new_commands_list(&ms->trash);
    if (!cmd_list)
        return NULL;

    while (ms->token)
    {
        t_one_command *curr_cmd;

        curr_cmd = create_new_command_node(&ms->trash);
        if (!curr_cmd)
            return NULL;

        ms->curr_cmd = curr_cmd;

        while (ms->token && ms->token->type != TOKEN_PIPE)
        {
            if (ms->token->type == TOKEN_WORD)
                add_word_to_cmd(curr_cmd, ms->token->value, &ms->trash);

            else if (ms->token->type == TOKEN_REDIR_IN
                  || ms->token->type == TOKEN_REDIR_OUT
                  || ms->token->type == TOKEN_REDIR_APPEND
                  || ms->token->type == TOKEN_REDIR_HEREDOC)
            {
                if (!ms->token->next || ms->token->next->type != TOKEN_WORD)
                    return NULL;

                add_file_to_cmd(
                    ms,
                    ms->token->next->value,
                    ms->token->type,
                    ms->token->next->dna
                );

                ms->token = ms->token->next; // skip filename
            }
            ms->token = ms->token->next;
        }

        ms->curr_cmd = NULL;

        if (!curr_cmd->cmd && !curr_cmd->files)
            return NULL;

        if (curr_cmd->cmd)
        {
            curr_cmd->cmd_type = find_cmd_type(curr_cmd->cmd);
            curr_cmd->executable = find_executable(curr_cmd->cmd[0]);
        }

        add_cmd_to_list(cmd_list, curr_cmd);

        if (ms->token && ms->token->type == TOKEN_PIPE)
            ms->token = ms->token->next;
    }

    return cmd_list;
}

