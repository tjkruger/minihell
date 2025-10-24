/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjkruger <tjkruger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 15:31:51 by tjkruger          #+#    #+#             */
/*   Updated: 2025/10/24 16:01:25 by tjkruger         ###   ########.fr       */
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
    TOKEN_REDIR_IN,
    TOKEN_REDIR_OUT,
    TOKEN_REDIR_APPEND,
    TOKEN_HEREDOC,
} t_token_type;


typedef struct s_token
{
    char            *value;
    t_token_type    type;
    struct  s_token *next;
}   t_token;

t_token *tokenize(char *input);
void    free_tokens(t_token *tokens);
void    print_tokens(t_token *tokens); 

#endif
