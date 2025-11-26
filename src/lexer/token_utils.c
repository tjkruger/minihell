/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjkruger <tjkruger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 15:32:25 by tjkruger          #+#    #+#             */
/*   Updated: 2025/11/26 11:58:20 by tjkruger         ###   ########.fr       */
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

char **extracted_token(char *str)
{
    char **list;
    char *token;
    char *dna;
    char *token_end;
    int   len;

    list = malloc(sizeof(char *) * 3);
    token_end = find_token_end(str);
    len = token_length(str, token_end);

    token = malloc(len + 1);
    dna   = malloc(len + 1);

    char *tp = token;
    char *dp = dna;

    int mode = 0;

    while (str < token_end)
    {
        if ((*str == '\'' || *str == '"'))
        {
            if (mode == 0)
                mode = *str;
            else if (mode == *str)
                mode = 0;

            str++;
            continue;
        }

        *tp++ = *str;
        *dp++ = (mode == 0 ? 'N' : (mode == '\'' ? 'S' : 'D'));

        str++;
    }

    *tp = '\0';
    *dp = '\0';

    list[0] = token;
    list[1] = dna;
    list[2] = NULL;

    return(list);
}




t_pretoken  *ft_split_for_token(char *input)
{
    t_pretoken  *t_list;
    int         j;
    int         arg_num;
    char        *str;
    char        **pair;

    j = 0;
    str = input;
    arg_num = how_many_token(str);
    if(arg_num == -1)
    {
        token_error();
        return(NULL);
    }
    t_list = malloc(sizeof(t_pretoken));//take the ** and feed it into their own **lists so i end up with **tokens and **dna
    t_list->token = malloc(sizeof(char *) * (arg_num + 1));
    t_list->dna= malloc(sizeof(char *) * (arg_num + 1));

    while(*str && j < arg_num)
    {
        pair = extracted_token(str);
        t_list->token[j] = malloc(sizeof(char) * (ft_strlen(pair[0]) + 1));
        t_list->dna[j]   = malloc(sizeof(char) * (ft_strlen(pair[1]) + 1));
        ft_strlcpy(t_list->token[j], pair[0], ft_strlen(pair[0]) + 1);
        ft_strlcpy(t_list->dna[j], pair[1], ft_strlen(pair[1]) + 1);
        str = find_token_end(str);
        while (*str && ft_isspace(*str))
            str++;

        j++;
    }
    t_list->token[j] = NULL;
    t_list->dna[j]   = NULL;
    return(t_list);
}



