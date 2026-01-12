/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: r2d2 <r2d2@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 15:32:25 by tjkruger          #+#    #+#             */
/*   Updated: 2026/01/13 00:02:20 by r2d2             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	token_length(char *str_start, char *str_end)
{
    int	length;

    length = (int)(str_end - str_start);
    return (length);
}

int	ft_isspace(char c) // 1 for space 0 for char
{
    if (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
        || c == '\r')
        return (1);
    return (0);
}

int	is_specialchar(char c)
{
    return (c == '|' || c == '<' || c == '>');
}

void	token_error(void)
{
    printf("please provide closing qoutes aswell would you ?\n");
}

char	*find_token_end(char *str)
{
    char	quote;

    while (str && *str && !ft_isspace(*str))
    {
        if (*str == '"' || *str == '\'')
        {
            quote = *str++;
            while (*str && *str != quote)
                str++;
            if (*str == '\0')
                return (NULL);
            str++;
        }
        else
            str++;
    }
    return (str);
}

char	**extracted_token(char *str, t_trash *trash)
{
    char	**list;
    char	*token;
    char	*dna;
    char	*token_end;
    int		len;
    char	*tp;
    char	*dp;
    char	q;

    token_end = find_token_end(str);
    if (!token_end)
        return (NULL);
    len = token_length(str, token_end);
    list = gc_malloc(trash, 3, sizeof(char *));
    if (!list)
        return (NULL);
    token = gc_malloc(trash, (len + 1), sizeof(char));
    dna = gc_malloc(trash, (len + 1), sizeof(char));
    if (!token || !dna)
        return (NULL);
    tp = token;
    dp = dna;
    int mode = 0; // 0 = outside quotes, '\'' = single quote, '"' = double quote
    while (str < token_end)
    {
        if ((*str == '"' || *str == '\'') && mode == 0)
        {
            q = *str;
            /* Empty quotes: "" or '' */
            if (*(str + 1) == q)
            {
                /* mark dna to indicate expansion blocked */
                *dp++ = 'Q'; /* Q = empty-quote boundary */
                str += 2;
                continue ;
            }
            mode = q;
            str++;
            continue ;
        }
        if (*str == mode && mode != 0)
        {
            mode = 0;
            str++;
            continue ;
        }
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
    return (list);
}

int	how_many_token(char *str)
{
    int		count;
    char	*end;

    count = 0;
    if (!str)
        return (0);
    while (*str)
    {
        while (*str && ft_isspace(*str))
            str++;
        if (!*str)
            break ;
        end = find_token_end(str);
        if (end == NULL) /* unclosed quote */
            return (-1);
        count++;
        str = end;
    }
    return (count);
}

t_pretoken	*allocate_pretoken(t_trash *trash, int arg_num)
{
    t_pretoken	*t_list;

    t_list = gc_malloc(trash, 1, sizeof(t_pretoken));
    if (!t_list)
        return (NULL);
    t_list->token = gc_malloc(trash, (arg_num + 1), sizeof(char *));
    t_list->dna = gc_malloc(trash, (arg_num + 1), sizeof(char *));
    if (!t_list->token || !t_list->dna)
        return (NULL);
    return (t_list);
}

int	fill_pretoken(t_pretoken *t_list, char *str, int arg_num, t_trash *trash)
{
    int		j;
    char	**pair;

    j = 0;
    while (*str && j < arg_num)
    {
        pair = extracted_token(str, trash);
        if (!pair)
            return (0);
        t_list->token[j] = pair[0];
        t_list->dna[j] = pair[1];
        str = find_token_end(str);
        while (*str && ft_isspace(*str))
            str++;
        j++;
    }
    t_list->token[j] = NULL;
    t_list->dna[j] = NULL;
    return (1);
}

t_pretoken	*ft_split_for_token(char *input, t_trash *trash)
{
    t_pretoken	*t_list;
    int			arg_num;

    arg_num = how_many_token(input);
    if (arg_num == -1)
    {
        token_error();
        return (NULL);
    }
    t_list = allocate_pretoken(trash, arg_num);
    if (!t_list)
        return (NULL);
    if (!fill_pretoken(t_list, input, arg_num, trash))
        return (NULL);
    return (t_list);
}
