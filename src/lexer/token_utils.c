/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: r2d2 <r2d2@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 15:32:25 by tjkruger          #+#    #+#             */
/*   Updated: 2025/11/25 03:40:18 by r2d2             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int token_length(char *str_start, char *str_end)
{
    int length;

    length = str_end - str_start;
    return(length);
}

// char *find_next_quote(char *start)
// {
//     char st_quote = *start; // either ' or "
//     char *str = start + 1;

//     while (*str && *str != st_quote)
//         str++;

//     if (*str == '\0')
//         return (NULL); //quote error
//     return (str);
// }


int ft_isspace(char c)// 1 for space 0 for char
{
    if (c == ' ' || c == '\t' || c == '\n'
    || c == '\v' || c == '\f' || c == '\r')
        return (1);
    return(0);
}

void    token_error(void)
{
    printf("pls think bevor wright stupid ... where second quote ???\n");
}

char *find_token_end(char *str)
{
    char quote;

    while (*str && !ft_isspace(*str))
    {
        if (*str == '"' || *str == '\'')
        {
            quote = *str++;
            while (*str && *str != quote)
                str++;

            if (*str == '\0')
                return(NULL);
            str++;
        }
        else
            str++;
    }
    return (str);
}


int how_many_token(char *str)
{
    int count;

    count = 0;
    while (*str && ft_isspace(*str))
        str++;

    while (*str)
    {
        count++;
        str = find_token_end(str);
        if(!str)
            return(-1);
        while (*str && ft_isspace(*str))
            str++;
    }
    return(count);
}

char *extracted_token(char *str)
{
    char *trim_str;
    char *token_end;
    char *start;
    int len;

    token_end = find_token_end(str);
    if (!token_end)
        return NULL;
    len = token_length(str, token_end);
    trim_str = malloc(len + 1);
    if (!trim_str)
        return NULL;
    start = trim_str;
    while (str < token_end)
    {
        if (*str == '"' || *str == '\'')
        {
            str++;
            while (str < token_end && *str != '"' && *str != '\'')
                *trim_str++ = *str++;
            str++;
        }
        else
            *trim_str++ = *str++;
    }
    *trim_str = '\0';
    return start;
}


char **ft_split_for_token(char *input)
{
    char **token_list;
    int num_tokens;
    int j = 0;
    char *str = input;
    char *tmp;

    num_tokens = how_many_token(str);
    if (num_tokens < 0)
    {
        token_error();
        return(NULL);
    }
    token_list = malloc(sizeof(char *) * (num_tokens + 1));
    if (!token_list)
        return NULL;
    while (*str && j < num_tokens)
    {

        while (*str && ft_isspace(*str))
            str++;
        if (*str)
        {
            tmp = extracted_token(str);
            token_list[j++] = tmp;
            str = find_token_end(str);
        }
    }
    token_list[j] = NULL;
    return token_list;
}



