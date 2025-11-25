/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: r2d2 <r2d2@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 15:32:25 by tjkruger          #+#    #+#             */
/*   Updated: 2025/11/25 18:26:18 by r2d2             ###   ########.fr       */
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

    return list;
}




t_pretoken  ft_split_for_token(char *input)
{
    t_pretoken  token_list;
    int         i;
    int         j;
    int         arg_num;
    char        *str;

    i = 0;
    j = 0;
    str = input;
    arg_num = how_many_token(str);
    token_list = malloc(sizeof(t_pretoken));//take the ** and feed it into their own **lists so i end up with **tokens and **dna
    
    while(*str && j < arg_num)
    {
        //something in here idk yet.
    }
    return(token_list);//return the struct for this then
}



