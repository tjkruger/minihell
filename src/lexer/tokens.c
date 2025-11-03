/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: r2d2 <r2d2@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 15:32:21 by tjkruger          #+#    #+#             */
/*   Updated: 2025/11/02 23:54:02 by r2d2             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"


t_token_type get_token_type(char *str)
{
    if (!str)
        return TOKEN_WORD;
    if (strcmp(str, "|") == 0)
        return TOKEN_PIPE;
    else if (strcmp(str, "<") == 0)
        return TOKEN_REDIRECT_IN;
    else if (strcmp(str, ">") == 0)
        return TOKEN_REDIRECT_OUT;
    else if (strcmp(str, ">>") == 0)
        return TOKEN_APPEND;
    else
        return TOKEN_WORD;
}


t_token tokenize(char  *input)
{
    t_token *head = NULL;
    t_token *tail = NULL;
    char **list;

    list = ft_split(*input);
    while(*list != NULL)
    {
        t_token *new = malloc(sizeof(t_token));
        if (!new)
            return (NULL); // handle malloc fail
        new->value = ft_strdup(*list);
        new->type = get_token_type(*list);
        new->next = NULL;
        if (!head)
        {
            head = new;
            tail = new;
        }
        else
        {
            tail->next = new;
            tail = new;
        }
        list++;
    }
    return(head);
}

void free_token_list(t_token *head)
{
    t_token *tmp;

    while (head)
    {
        tmp = head->next;
        free(head->value);
        free(head);
        head = tmp;
    }
}

