/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_command_list.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: r2d2 <r2d2@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 13:31:35 by tjkruger          #+#    #+#             */
/*   Updated: 2025/11/18 15:09:39 by r2d2             ###   ########.fr       */
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

t_file_node *create_file_node(char *value, t_token_type redir_type)
{
    t_file_node *node = malloc(sizeof(t_file_node));
    if (!node)
        return NULL;
    node->filename = ft_strdup(value);
    node->redir_type = redir_type;  // store enum value
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


int find_cmd_type(char **cmd)
{
    (void) cmd;
    //bunch of else if statements with strcmp or so ...
    //bis zum ersten ' ' suchen und dann den command comparen zu den buildins no ?
    //also 1 for buildin and 0 for external ?
    return (1);
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

char    *trim_arg(char *str)
{
    char *str2;

    printf("%s \n", str);
    str2 = ft_strdup(str + 2);
    printf("%s \n", str2);
    free(str);
    return(str2);
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
                add_file_to_cmd(curr_cmd, tokens->next->value, tokens->type);
                tokens = tokens->next; // skip filename
            }
            tokens = tokens->next;
        }

        curr_cmd->cmd_type = find_cmd_type(curr_cmd->cmd); // determine buildin or not
        curr_cmd->executable = find_executable(curr_cmd->cmd[0]);
        if(curr_cmd->executable)
            curr_cmd->cmd[0] = trim_arg(curr_cmd->cmd[0]);
        add_cmd_to_list(cmd_list, curr_cmd);

        if (tokens && tokens->type == TOKEN_PIPE)
            tokens = tokens->next;
    }

    return cmd_list;
}
