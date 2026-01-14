/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token-pretoken_management3.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjkruger <tjkruger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 12:07:01 by tjkruger          #+#    #+#             */
/*   Updated: 2026/01/14 13:47:21 by tjkruger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	append_subtokens(t_token **head, t_token **tail, t_token *sub)
{
	if (!sub)
		return ;
	if (!*head)
	{
		*head = sub;
		*tail = sub;
		while ((*tail)->next)
			*tail = (*tail)->next;
		return ;
	}
	(*tail)->next = sub;
	while ((*tail)->next)
		*tail = (*tail)->next;
}

/* initialize lexer context used by split_pretoken */
t_lexer_ctx	init_lexer_ctx(char *text, char *dna, t_ms *ms)
{
	t_lexer_ctx	ctx;

	ctx.head = NULL;
	ctx.text = text;
	ctx.dna = dna;
	ctx.trash = &ms->trash;
	ctx.i = 0;
	ctx.flag = 0;
	ctx.txt_buf = NULL;
	ctx.dna_buf = NULL;
	return (ctx);
}

t_token	*split_pretoken(char *text, char *dna, t_ms *ms)
{
	t_lexer_ctx	ctx;

	ctx = init_lexer_ctx(text, dna, ms);
	while (text[ctx.i])
	{
		if (dna[ctx.i] == 'N' && is_op(text[ctx.i]))
		{
			flush_word(&ctx.head, &ctx.txt_buf, &ctx.dna_buf, ctx.trash);
			ctx.flag = make_op_token(&ctx);
			if (ctx.flag)
				ctx.i++;
		}
		else
		{
			ctx.txt_buf = append_char(ctx.txt_buf, text[ctx.i], ctx.trash);
			ctx.dna_buf = append_char(ctx.dna_buf, dna[ctx.i], ctx.trash);
		}
		ctx.i++;
	}
	flush_word(&ctx.head, &ctx.txt_buf, &ctx.dna_buf, ctx.trash);
	return (ctx.head);
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
		if (end == NULL)
			return (-1);
		count++;
		str = end;
	}
	return (count);
}
