/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjkruger <tjkruger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 15:32:21 by tjkruger          #+#    #+#             */
/*   Updated: 2026/01/13 16:38:39 by tjkruger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*split_pretoken(char *text, char *dna, t_ms *ms)
{
	t_token		*head;
	char		*txt_buf;
	char		*dna_buf;
	t_lexer_ctx	ctx;
	int			i;
	int			flag;

	head = NULL;
	txt_buf = NULL;
	dna_buf = NULL;
	i = 0;
	flag = 0;
	ctx.head = &head;
	ctx.text = text;
	ctx.dna = dna;
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
	return (head);
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

t_token	*tokenize(char *input, t_ms *ms)
{
	t_token		*single;
	t_pretoken	*pretoken;
	t_token		*head;
	t_token		*tail;
	t_token		*sub;
	int			i;

	/* HEREDOC MODE:*/
	if (ms->all_commands)
	{
		single = gc_malloc(&ms->trash, 1, sizeof(t_token));
		if (!single)
			return (NULL);
		single->value = gc_strdup(&ms->trash, input);
		single->dna = NULL;
		single->type = TOKEN_WORD;
		single->next = NULL;
		return (single);
	}
	/* NORMAL MODE: full tokenizer */
	head = NULL;
	tail = NULL;
	i = 0;
	pretoken = ft_split_for_token(input, &ms->trash);
	if (!pretoken)
		return (NULL);
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
