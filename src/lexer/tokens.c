/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjkruger <tjkruger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 15:32:21 by tjkruger          #+#    #+#             */
/*   Updated: 2026/01/14 13:46:47 by tjkruger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Validate finished token bevore sending the list back*/
int	validate_token(t_token *head)
{
	t_token	*prev;

	prev = NULL;
	while (head)
	{
		if (!prev && head->type == TOKEN_PIPE)
			return (0);
		else if (!head->next && head->type == TOKEN_PIPE)
			return (0);
		else if (prev && prev->type == TOKEN_PIPE && head->type == TOKEN_PIPE)
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

/* Handle heredoc mode: return a single token containing raw input. */
static t_token	*handle_heredoc(char *input, t_ms *ms)
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

/* Handle normal tokenization: full pretoken + split processing. */
static t_token	*handle_normal(char *input, t_ms *ms)
{
	t_pretoken	*pretoken;
	t_token		*head;
	t_token		*tail;
	t_token		*sub;
	int			i;

	head = NULL;
	tail = NULL;
	i = 0;
	pretoken = ft_split_for_token(input, &ms->trash);
	if (!pretoken)
		return (NULL);
	while (pretoken->token[i])
	{
		sub = split_pretoken(pretoken->token[i], pretoken->dna[i], ms);
		append_subtokens(&head, &tail, sub);
		i++;
	}
	if (!validate_token(head))
		return (NULL);
	return (head);
}

/* Tokenize input: dispatch to heredoc or normal handler. */
t_token	*tokenize(char *input, t_ms *ms)
{
	if (ms && ms->all_commands)
		return (handle_heredoc(input, ms));
	return (handle_normal(input, ms));
}
