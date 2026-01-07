/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjkruger <tjkruger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 15:32:21 by tjkruger          #+#    #+#             */
/*   Updated: 2026/01/07 18:01:05 by tjkruger         ###   ########.fr       */
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


char *ft_strjoin_free(char *s1, char c, t_trash *trash)
{
    int len;
    char *new_str;
    int i;

    i = 0;
    len = 0;
    while (s1 && s1[len] != '\0')
        len++;

    new_str = gc_malloc(trash, len + 2, sizeof(char));
    if (!new_str)
        return NULL;

    while(i < len)
    {
        new_str[i] = s1[i];
        i++;
    }

    new_str[len] = c;
    new_str[len + 1] = '\0';



    return new_str;
}

char *append_char(char *s, char c, t_trash *trash)
{
    return ft_strjoin_free(s, c, trash);
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
int make_op_token(t_lexer_ctx *ctx)
{
    char *op;
    char *opd;
    int  flag;

    flag = 0;
    if (ctx->text[ctx->i] == ctx->text[ctx->i + 1]
        && ctx->text[ctx->i] != '|')
    {
        op  = gc_malloc(ctx->trash, 3, sizeof(char));
        opd = gc_malloc(ctx->trash, 3, sizeof(char));

        op[0]  = ctx->text[ctx->i];
        op[1]  = ctx->text[ctx->i + 1];
        op[2]  = '\0';

        opd[0] = ctx->dna[ctx->i];
        opd[1] = ctx->dna[ctx->i + 1];
        opd[2] = '\0';

        flag = 1;
    }
    else
    {
        op  = gc_malloc(ctx->trash, 2, sizeof(char));
        opd = gc_malloc(ctx->trash, 2, sizeof(char));

        op[0]  = ctx->text[ctx->i];
        op[1]  = '\0';

        opd[0] = ctx->dna[ctx->i];
        opd[1] = '\0';
    }

    push_token(ctx->head, op, opd, ctx->trash);
    return flag;
}


t_token *split_pretoken(char *text, char *dna, t_ms *ms)
{
    t_token     *head = NULL;
    char        *txt_buf = NULL;
    char        *dna_buf = NULL;
    t_lexer_ctx ctx;
    int         i = 0;
    int         flag = 0;

    ctx.head  = &head;
    ctx.text  = text;
    ctx.dna   = dna;
    ctx.trash = &ms->trash;

    while (text[i])
    {
        if (dna[i] == 'N' && is_op(text[i]))
        {
            flush_word(&head, &txt_buf, &dna_buf, &ms->trash);
            ctx.i = i;
            flag = make_op_token(&ctx);
            if (flag)
                i++;
        }
        else
        {
            txt_buf = append_char(txt_buf, text[i], &ms->trash);
            dna_buf = append_char(dna_buf, dna[i], &ms->trash);
        }
        i++;
    }
    flush_word(&head, &txt_buf, &dna_buf, &ms->trash);
    return head;
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

t_token *tokenize(char *input, t_ms *ms)
{
    t_token *single;

    /* HEREDOC MODE:*/
    if (ms->all_commands)
    {
        single = gc_malloc(&ms->trash, 1, sizeof(t_token));
        if (!single)
            return NULL;

        single->value = gc_strdup(&ms->trash, input);
        single->dna = NULL;
        single->type = TOKEN_WORD;
        single->next = NULL;
        return single;
    }

    /* NORMAL MODE: full tokenizer */
    t_pretoken  *pretoken;
    t_token     *head = NULL;
    t_token     *tail = NULL;
    t_token     *sub;
    int         i = 0;
    pretoken = ft_split_for_token(input, &ms->trash);
    if (!pretoken)
        return NULL;

    while (pretoken->token[i])
    {
        sub = split_pretoken(pretoken->token[i], pretoken->dna[i], ms);
        while (sub)
        {
            if (!head)
                head = tail = sub;
            else
            {
                tail->next = sub;
                tail = sub;
            }
            sub = sub->next;
        }
        i++;
    }

    if (!validate_token(head))
        return NULL;

    return head;
}

