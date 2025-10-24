/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjkruger <tjkruger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 15:32:25 by tjkruger          #+#    #+#             */
/*   Updated: 2025/10/24 16:17:17 by tjkruger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "minishell.h"
#include "tokens.h"
#include <string.h>


//create the node for a token
t_token *create_token(char *value)
{
    t_token *token;
    t_token_type type;
    
    // WHO ARRREE YOUUO ?? for the token also remove all the strcmp in here and switch for strn compare
    if (strcmp(value, "|") == 0)
        type = TOKEN_PIPE;
    else if (strcmp(value, "<") == 0)
        type = TOKEN_REDIR_IN;
    else if (strcmp(value, ">") == 0)
        type = TOKEN_REDIR_OUT;
    else if (strcmp(value, "<<") == 0)
        type = TOKEN_HEREDOC;
    else if (strcmp(value, ">>") == 0)
        type = TOKEN_REDIR_APPEND;
    else
        type = TOKEN_WORD;
    
    token = malloc(sizeof(t_token));
    if (!token)
        return (NULL);
    token->value = strdup(value);
    if (!token->value)
    {
        free(token);
        return (NULL);
    }
    token->type = type;
    token->next = NULL;
    return (token);
}


void add_token(t_token **head, t_token *new_token)
{
    t_token *current;
    
    if (!*head)
    {
        *head = new_token;
        return;
    }
    current = *head;
    while (current->next)
        current = current->next;
    current->next = new_token;
}

// Free all of em 
void free_tokens(t_token *tokens)
{
    t_token *temp;
    
    while (tokens)
    {
        temp = tokens;
        tokens = tokens->next;
        free(temp->value);
        free(temp);
    }
}

// Debug function to print tokens keep in here for now 
// void print_tokens(t_token *tokens)
// {
//     t_token *current = tokens;
//     char    *type_names[] = {"WORD", "PIPE", "REDIR_IN", 
//                              "REDIR_OUT", "REDIR_APPEND", "HEREDOC"};
    
//     printf("\n=== TOKENS ===\n");
//     while (current)
//     {
//         printf("[%s]: '%s'\n", type_names[current->type], current->value);
//         current = current->next;
//     }
//     printf("==============\n\n");
// }


// int main(void)
// {
//     t_token *tokens;
//     t_token *token1;
//     t_token *token2;
    
//     tokens = NULL;
    
//     token1 = create_token("echo");
//     token2 = create_token("|");
    
//     add_token(&tokens, token1);
//     add_token(&tokens, token2);
    
//     print_tokens(tokens);
    
//     free_tokens(tokens);
    
//     return 0;
// }