/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjkruger <tjkruger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 15:32:25 by tjkruger          #+#    #+#             */
/*   Updated: 2025/12/13 17:16:55 by tjkruger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int token_length(char *str_start, char *str_end)
{
    int length;

    length = str_end - str_start;
    return(length);
}

int ft_isspace(char c)// 1 for space 0 for char
{
    if (c == ' ' || c == '\t' || c == '\n'
    || c == '\v' || c == '\f' || c == '\r')
        return (1);
    return(0);
}

int is_specialchar(char c)
{
    return (c == '|' || c == '<' || c == '>');
}


void    token_error(void)
{
    printf("pls think bevor wright stupid ... where second quote ???\n");
}

char *find_token_end(char *str, t_all_commands *cmds)
{
    char quote;
    quote = NULL;
    if(!cmds)
    {
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
    }
    
    return (str);
}


int how_many_token(char *str, t_all_commands *cmds)
{
    int count;

    count = 0;
    while (*str && ft_isspace(*str))
        str++;

    while (*str)
    {
        count++;
        str = find_token_end(str, cmds);
        if(!str)
            return(-1);
        while (*str && ft_isspace(*str))
            str++;
    }
    return(count);
}

char **extracted_token(char *str, t_all_commands *cmds)
{
    char **list;
    char *token;
    char *dna;
    char *token_end;
    int   len;

    list = malloc(sizeof(char *) * 3);
    token_end = find_token_end(str, cmds);
    len = token_length(str, token_end);

    token = malloc(len + 1);
    dna   = malloc(len + 1);

    char *tp = token;
    char *dp = dna;

    int mode = 0; // 0 = outside quotes, '\'' = single quote, '"' = double quote

    while (str < token_end)
    {
        // starting quotes, only if outside any quote
        if (*str == '\'' && mode == 0 && !cmds)
        {
            mode = '\'';
            str++;
            continue;
        }
        if (*str == '"' && mode == 0 && !cmds)
        {
            mode = '"';
            str++;
            continue;
        }

        // closing quote of current mode
        if (*str == mode && mode != 0)
        {
            mode = 0;
            str++;
            continue;
        }

        // normal char or quote inside different type
        *tp++ = *str;
        if (mode == 0)
            *dp++ = 'N';
        else if (mode == '\'')
            *dp++ = 'S';
        else
            *dp++ = 'D';

        str++;
    }

    *tp = '\0';
    *dp = '\0';

    list[0] = token;
    list[1] = dna;
    list[2] = NULL;

    return list;
}





t_pretoken  *ft_split_for_token(char *input, t_all_commands *cmds)
{
    t_pretoken  *t_list;
    int         j;
    int         arg_num;
    char        *str;
    char        **pair;

    j = 0;
    str = input;
    arg_num = how_many_token(str, cmds);
    if(arg_num == -1)
    {
        token_error();
        return(NULL);
    }
    t_list = malloc(sizeof(t_pretoken));
    t_list->token = malloc(sizeof(char *) * (arg_num + 1));
    t_list->dna= malloc(sizeof(char *) * (arg_num + 1));

    while(*str && j < arg_num)
    {
        pair = extracted_token(str, cmds);
        t_list->token[j] = malloc(sizeof(char) * (ft_strlen(pair[0]) + 1));
        t_list->dna[j]   = malloc(sizeof(char) * (ft_strlen(pair[1]) + 1));
        ft_strlcpy(t_list->token[j], pair[0], ft_strlen(pair[0]) + 1);
        ft_strlcpy(t_list->dna[j], pair[1], ft_strlen(pair[1]) + 1);
        str = find_token_end(str, cmds);
        while (*str && ft_isspace(*str))
            str++;

        j++;
    }
    t_list->token[j] = NULL;
    t_list->dna[j]   = NULL;
    return(t_list);
}



