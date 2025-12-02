/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjkruger <tjkruger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 15:32:21 by tjkruger          #+#    #+#             */
/*   Updated: 2025/11/26 11:59:06 by tjkruger         ###   ########.fr       */
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

char *append_char(char *s, char c)
{
    char temp[2];

    temp[0] = c;
    temp[1] = '\0';

    if (!s)
        return ft_strdup(temp);   // first char → simple dup

    return ft_strjoin(s, temp);   // later chars → join
}




void push_token(t_token **head, char *value, char *dna)
{
    t_token *new = malloc(sizeof(t_token));
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


void flush_word(t_token **head, char **txt_buf, char **dna_buf)
{
    if (*txt_buf == NULL || (*txt_buf)[0] == '\0')
        return ;
    push_token(head, *txt_buf, *dna_buf);

    *txt_buf = NULL;
    *dna_buf = NULL;
}


void make_op_token(t_token **head, char op, char dna)
{
    char *v = malloc(2);
    char *d = malloc(2);

    v[0] = op;
    v[1] = '\0';

    d[0] = dna;
    d[1] = '\0';

    push_token(head, v, d);
}


t_token *split_pretoken(char *text, char *dna)
{
    t_token *head = NULL;
    char    *txt_buf;
    char    *dna_buf;
    int     i = 0;

    txt_buf = NULL;
    dna_buf = NULL;
    while (text[i])
    {
        if (dna[i] == 'N' && is_op(text[i]))
        {
            flush_word(&head, &txt_buf, &dna_buf);
            make_op_token(&head, text[i], dna[i]);
        }
        else
        {
            txt_buf = append_char(txt_buf, text[i]);
            dna_buf = append_char(dna_buf, dna[i]);
        }
        i++;
    }
    flush_word(&head, &txt_buf, &dna_buf);
    return (head);
}


t_token *tokenize(char *input)
{
    t_pretoken  *pretoken;
    t_token     *head = NULL;
    t_token     *tail = NULL;
    t_token     *sub;
    int         i;
    pretoken = ft_split_for_token(input);
    printf("gotcha bitch\n");
    fflush(stdout);
    if (!pretoken)
        return (NULL);

    i = 0;
    while (pretoken->token[i])
    {
        // split each pretoken into real tokens
        sub = split_pretoken(pretoken->token[i], pretoken->dna[i]);

        // append the resulting mini-list to the main list
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

    free_pretoken(pretoken);
    return (head);
}


//need to fix this case here: "hel'lo there" so the ' must be printed out with the rest curr gets skipped
