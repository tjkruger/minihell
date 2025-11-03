/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: r2d2 <r2d2@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 15:31:51 by tjkruger          #+#    #+#             */
/*   Updated: 2025/11/03 12:17:01 by r2d2             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef TOKENS_H
#define TOKENS_H


#include <stdlib.h>
#include <stdio.h>

typedef enum    e_token_type
{
    TOKEN_WORD,
    TOKEN_PIPE,
    TOKEN_REDIR_IN,//<
    TOKEN_REDIR_OUT,//>
    TOKEN_REDIR_APPEND,//<<
    // >> heredoc
} t_token_type;

typedef struct s_token
{
    char            *value;
    t_token_type    type;
    struct  s_token *next;
}   t_token;

typedef struct s_one_command
{
    struct s_one_command *next;
    int cmd_type;
    char **cmd;
    t_file_list *files;
} t_one_command;

typedef struct s_all_commands
{
    int syntax_error;
    t_one_command *head;
    t_one_command *tail;
    ssize_t size;
} t_all_commands;


t_token *tokenize(char *input);

#endif
