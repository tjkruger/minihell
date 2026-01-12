/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: r2d2 <r2d2@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 15:32:21 by tjkruger          #+#    #+#             */
/*   Updated: 2026/01/13 00:04:19 by r2d2             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token_type	get_token_type(char *str)
{
    if (!str)
        return (TOKEN_WORD);
    if (strcmp(str, "|") == 0)
        return (TOKEN_PIPE);
    else if (strcmp(str, "<") == 0)
        return (TOKEN_REDIR_IN);
    else if (strcmp(str, ">") == 0)
        return (TOKEN_REDIR_OUT);
    else if (strcmp(str, ">>") == 0)
        return (TOKEN_REDIR_APPEND);
    else if (strcmp(str, "<<") == 0)
        return (TOKEN_REDIR_HEREDOC);
    else
        return (TOKEN_WORD);
}

int	is_op(char c)
{
    return (c == '>' || c == '<' || c == '|');
}

char	*ft_strjoin_free(char *s1, char c, t_trash *trash)
{
    int		len;
    char	*new_str;
    int		i;

    i = 0;
    len = 0;
    while (s1 && s1[len] != '\0')
        len++;
    new_str = gc_malloc(trash, (len + 2), sizeof(char));
    if (!new_str)
        return (NULL);
    while (i < len)
    {
        new_str[i] = s1[i];
        i++;
    }
    new_str[len] = c;
    new_str[len + 1] = '\0';
    return (new_str);
}

char	*append_char(char *s, char c, t_trash *trash)
{
    return (ft_strjoin_free(s, c, trash));
}

/* allocate and push a token node using GC */
void	push_token(t_token **head, char *value, char *dna, t_trash *trash)
{
    t_token	*new;
    t_token	*tmp;

    new = gc_malloc(trash, 1, sizeof(t_token));
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

void	flush_word(t_token **head, char **txt_buf, char **dna_buf,
        t_trash *trash)
{
    if (*txt_buf == NULL || (*txt_buf)[0] == '\0')
        return ;
    push_token(head, *txt_buf, *dna_buf, trash);
    *txt_buf = NULL;
    *dna_buf = NULL;
}

/* make op token using GC (op/opd allocated via gc_malloc) */
int	make_op_token(t_lexer_ctx *ctx)
{
    if (is_double_op(ctx))
        return (make_double_op(ctx));
    make_single_op(ctx);
    return (0);
}

int	make_double_op(t_lexer_ctx *ctx)
{
    char	*op;
    char	*opd;

    op = gc_malloc(ctx->trash, 3, sizeof(char));
    opd = gc_malloc(ctx->trash, 3, sizeof(char));
    op[0] = ctx->text[ctx->i];
    op[1] = ctx->text[ctx->i + 1];
    op[2] = '\0';
    opd[0] = ctx->dna[ctx->i];
    opd[1] = ctx->dna[ctx->i + 1];
    opd[2] = '\0';
    push_token(ctx->head, op, opd, ctx->trash);
    return (1);
}

void	make_single_op(t_lexer_ctx *ctx)
{
    char	*op;
    char	*opd;

    op = gc_malloc(ctx->trash, 2, sizeof(char));
    opd = gc_malloc(ctx->trash, 2, sizeof(char));
    op[0] = ctx->text[ctx->i];
    op[1] = '\0';
    opd[0] = ctx->dna[ctx->i];
    opd[1] = '\0';
    push_token(ctx->head, op, opd, ctx->trash);
}

int	is_double_op(t_lexer_ctx *ctx)
{
    return (ctx->text[ctx->i] == ctx->text[ctx->i + 1]
        && ctx->text[ctx->i] != '|');
}
void	init_split_ctx(t_lexer_ctx *ctx, t_token **head,
        char *text, char *dna, t_ms *ms)
{
    *head = NULL;
    ctx->head = head;
    ctx->text = text;
    ctx->dna = dna;
    ctx->trash = &ms->trash;
    ctx->txt_buf = NULL;
    ctx->dna_buf = NULL;
}
void	handle_op_char(t_lexer_ctx *ctx, int *i, t_ms *ms)
{
    int	flag;

    flush_word(ctx->head, &ctx->txt_buf, &ctx->dna_buf, &ms->trash);
    ctx->i = *i;
    flag = make_op_token(ctx);
    if (flag)
        (*i)++;
}

void	handle_word_char(t_lexer_ctx *ctx, char *text, char *dna, int i)
{
    ctx->txt_buf = append_char(ctx->txt_buf, text[i], ctx->trash);
    ctx->dna_buf = append_char(ctx->dna_buf, dna[i], ctx->trash);
}
t_token	*split_pretoken(char *text, char *dna, t_ms *ms)
{
    t_token		*head;
    t_lexer_ctx	ctx;
    int			i;

    init_split_ctx(&ctx, &head, text, dna, ms);
    i = 0;
    while (text[i])
    {
        if (is_op_char(dna, text, i))
            handle_op_char(&ctx, &i, ms);
        else
            handle_word_char(&ctx, text, dna, i);
        i++;
    }
    flush_word(&head, &ctx.txt_buf, &ctx.dna_buf, &ms->trash);
    return (head);
}



int	is_op_char(char *dna, char *text, int i)
{
    return (dna && dna[i] == 'N' && is_op(text[i]));
}





int	validate_token(t_token *head)
{
    t_token	*prev;

    prev = NULL;
    while (head)
    {
        if (!prev && head->type == TOKEN_PIPE) // first must be a word
            return (0);
        else if (!head->next && head->type == TOKEN_PIPE) // last must be a word
            return (0);
        else if (prev && prev->type == TOKEN_PIPE && head->type == TOKEN_PIPE)
            // no double pipes
            return (0);
        else if (prev && (prev->type == TOKEN_REDIR_IN
                || prev->type == TOKEN_REDIR_OUT
                || prev->type == TOKEN_REDIR_APPEND
                || prev->type == TOKEN_REDIR_HEREDOC))
        {
            if (head->type != TOKEN_WORD)
                return (0);
        }
        prev = head;
        head = head->next;
    }
    return (1);
}

void	append_subtokens(t_token **head, t_token **tail, t_token *sub)
{
    while (sub)
    {
        if (!*head)
            *head = *tail = sub;
        else
        {
            (*tail)->next = sub;
            *tail = sub;
        }
        sub = sub->next;
    }
}

t_token	*tokenize_normal(char *input, t_ms *ms)
{
    t_pretoken	*pre;
    t_token		*head;
    t_token		*tail;
    t_token		*sub;
    int			i;

    head = NULL;
    tail = NULL;
    i = 0;
    pre = ft_split_for_token(input, &ms->trash);
    if (!pre)
        return (NULL);
    while (pre->token[i])
    {
        sub = split_pretoken(pre->token[i], pre->dna[i], ms);
        append_subtokens(&head, &tail, sub);
        i++;
    }
    return (head);
}

t_token	*tokenize_heredoc(char *input, t_ms *ms)
{
    t_token	*single;

    single = gc_malloc(&ms->trash, 1, sizeof(t_token));
    if (!single)
        return (NULL);
    single->value = gc_strdup(&ms->trash, input);
    single->dna = NULL;
    single->type = TOKEN_WORD;
    single->next = NULL;
    return (single);
}

t_token	*tokenize(char *input, t_ms *ms)
{
    t_token	*head;

    if (ms && ms->all_commands)
        return (tokenize_heredoc(input, ms));
    head = tokenize_normal(input, ms);
    if (!head)
        return (NULL);
    if (!validate_token(head))
        return (NULL);
    return (head);
}

