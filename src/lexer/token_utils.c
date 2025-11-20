/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: r2d2 <r2d2@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 15:32:25 by tjkruger          #+#    #+#             */
/*   Updated: 2025/11/20 02:00:58 by r2d2             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int token_length(char *str_start, char *str_end)
{
    int length;

    length = str_end - str_start;
    return(length)
}

char *pos_of_token_end(char *str, char delimiter)
{
    char *str_end;
    int i;

    i = 0;
    str_end = str + 1;
    while(str_end[i] != delimiter )
    {
        if(str[i] == '\0')
            return(NULL);//throw error here bc no second ' or " 
        if(str_end[i] == delimiter)
            return(str_end + i);
        i++;
    }
}

int isspace(char c)// 1 for space 0 for char
{
    if (c == ' ' || c == '\t' || c == '\n'
    || c == '\v' || c == '\f' || c == '\r')
        return (1);
    return(0);
}

int how_many_token(char *str)
{
    int count;
    int i;
    char *end;

    i = 0;
    count = 0;
    while(str[i] != '\0')
    {
        while(str[i] && isspace(str[i]))
            i++;
        if(str[i] == '"' || str[i] == '\'')
            {
                end = pos_of_token_end(str, str[i]);
                i += token_length(str + i, end);
                count++;
            }
        else
        {
            while(str[i] && !isspace(str[i]))
            {
                if(str[i] == '"' || str[i] == '\'')
                {
                    end = pos_of_token_end(str + i, str[i]);
                    i += token_length(str + i, end);
                }
                else
                {
                    i++;
                }
            }
            count++;
        }
        i++;
    }
    return(count);
}

char    **ft_split_for_token(char *input);
{
    char **token_list;
    int i;
    char *str;
    str = input;
    i = how_many_token(str);
    token_list = malloc(sizeof(char *) * (i + 1));
    i = 0;
    // now copy all the tokens into the designatet areas no ?
    return(token_list);
}

//muss schauen wenn es kein 2 " gibt muss ich zum ' ' zurueck und danach trennen


// Correct boundaries for unquoted tokens
// Missing substring copy logic
// Recognize different token types
// Unterminated quote detection
// Reuse helpers across counting & splitting