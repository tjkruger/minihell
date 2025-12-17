/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: r2d2 <r2d2@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 15:32:21 by tjkruger          #+#    #+#             */
/*   Updated: 2025/12/17 23:44:51 by r2d2             ###   ########.fr       */
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
        return TOKEN_REDIR_IN;
    else if (strcmp(str, ">") == 0)
        return TOKEN_REDIR_OUT;
    else if (strcmp(str, ">>") == 0)
        return TOKEN_REDIR_APPEND;
    else if (strcmp(str, "<<") == 0)
        return TOKEN_REDIR_HEREDOC;
    else
        return TOKEN_WORD;
}

int is_op(char c)
{
    return (c == '>' || c == '<' || c == '|');
}


char *ft_strjoin_free(char *s1, char c)
{
    int len;
    char *new_str;
    int i;

    i = 0;
    len = 0;
    while (s1 && s1[len] != '\0')
        len++;

    new_str = malloc(len + 2);
    if (!new_str)
        return NULL;

    while(i < len)
    {
        new_str[i] = s1[i];
        i++;
    }

    new_str[len] = c;
    new_str[len + 1] = '\0';

    if (s1)
        free(s1);

    return new_str;
}

char *append_char(char *s, char c)
{
    return ft_strjoin_free(s, c);   // later chars → join
}

/* allocate and push a token node using GC */
void push_token(t_token **head, char *value, char *dna, t_trash *trash)
{
    t_token *new = gc_malloc(trash, 1, sizeof(t_token));
    t_token *tmp;

    if (!new)
        return ;
    new->value = value;
    new->dna = dna;
    new->type = get_token_type(value);
    new->next = NULL;

    if (!*head)
    {
        *head = new;
        return ;
    }
    tmp = *head;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new;
}

void flush_word(t_token **head, char **txt_buf, char **dna_buf, t_trash *trash)
{
    if (*txt_buf == NULL || (*txt_buf)[0] == '\0')
        return ;
    push_token(head, *txt_buf, *dna_buf, trash);

    *txt_buf = NULL;
    *dna_buf = NULL;
}

/* make op token using GC (op/opd allocated via gc_malloc) */
int make_op_token(t_token **head,char *str,char *dna, int i, t_trash *trash)
{
    char *op;
    char *opd;
    int flag;

    flag = 0;

    if (str[i] == str[i + 1] && str[i] != '|')
    {
        op = gc_malloc(trash, 3, sizeof(char));
        opd = gc_malloc(trash, 3, sizeof(char));
        
        op[0] = str[i];
        op[1] = str[i + 1];
        op[2] = '\0';

        opd[0] = dna[i];
        opd[1] = dna[i + 1];
        opd[2] = '\0';
        flag = 1;
    }
    else
    {
        op = gc_malloc(trash, 2, sizeof(char));
        opd = gc_malloc(trash, 2, sizeof(char));

        op[0] = str[i];
        op[1] = '\0';

        opd[0] = dna[i];
        opd[1] = '\0';
    }

    push_token(head, op, opd, trash);
    return (flag);
}

t_token *split_pretoken(char *text, char *dna, t_trash *trash)
{
    t_token *head = NULL;
    char    *txt_buf = NULL;
    char    *dna_buf = NULL;
    int     i = 0;
    int     flag = 0;

    while (text[i])
    {
        if (dna[i] == 'N' && is_op(text[i]))
        {
            flush_word(&head, &txt_buf, &dna_buf, trash);
            flag = make_op_token(&head, text, dna, i, trash);
            if (flag)
                i++;
        }
        else
        {
            txt_buf = append_char(txt_buf, text[i]);
            dna_buf = append_char(dna_buf, dna[i]);
        }
        i++;
    }
    flush_word(&head, &txt_buf, &dna_buf, trash);
    return (head);
}

int validate_token(t_token  *head)
{
    t_token *prev = NULL;
    
    while(head)
    {
        if(!prev && head->type == TOKEN_PIPE)//first must be a word
            return(0);
        else if(!head->next && head->type == TOKEN_PIPE)//last must be a word
            return(0);
        else if(prev && prev->type == TOKEN_PIPE && head->type == TOKEN_PIPE)//no double pipes
            return(0);
        else if (prev && (
                prev->type == TOKEN_REDIR_IN ||
                prev->type == TOKEN_REDIR_OUT ||
                prev->type == TOKEN_REDIR_APPEND ||
                prev->type == TOKEN_REDIR_HEREDOC))
        {
            if (head->type != TOKEN_WORD)
                return 0;
        }
        prev = head;
        head = head->next;
    }
    return(1);
}

t_token *tokenize(char *input, t_trash *trash)
{
    t_pretoken  *pretoken;
    t_token     *head = NULL;
    t_token     *tail = NULL;
    t_token     *sub;
    int         i;
    pretoken = ft_split_for_token(input, trash);
    if (!pretoken)
        return (NULL);

    i = 0;
    while (pretoken->token[i])
    {
        /* split each pretoken into real tokens */
        sub = split_pretoken(pretoken->token[i], pretoken->dna[i], trash);

        /* append the resulting mini-list to the main list */
        while (sub)
        {
            if (!head)
            {
                head = sub;
                tail = sub;
            }
            else
            {
                tail->next = sub;
                tail = sub;
            }
            sub = sub->next;
        }
        i++;
    }
    if(!validate_token(head))
        return(NULL);

    /* pretoken and all allocations are GC-managed now, do not free here */
    return (head);
}
