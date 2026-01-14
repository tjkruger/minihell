/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_append_helper.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjkruger <tjkruger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 16:37:40 by tjkruger          #+#    #+#             */
/*   Updated: 2026/01/14 15:42:14 by tjkruger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin_free(char *s1, char c, t_trash *trash)
{
	int		len;
	char	*new_str;
	int		i;

	i = 0;
	len = 0;
	while (s1 && s1[len] != '\0')
		len++;
	new_str = gc_malloc(trash, len + 2, sizeof(char));
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
	char	*op;
	char	*opd;

	if (ctx->text[ctx->i] == ctx->text[ctx->i + 1] && ctx->text[ctx->i] != '|')
	{
		op = gc_malloc(ctx->trash, 3, sizeof(char));
		opd = gc_malloc(ctx->trash, 3, sizeof(char));
		op[0] = ctx->text[ctx->i];
		op[1] = ctx->text[ctx->i + 1];
		op[2] = '\0';
		opd[0] = ctx->dna[ctx->i];
		opd[1] = ctx->dna[ctx->i + 1];
		opd[2] = '\0';
		ctx->opflag = 1;
	}
	else
	{
		op = gc_malloc(ctx->trash, 2, sizeof(char));
		opd = gc_malloc(ctx->trash, 2, sizeof(char));
		op[0] = ctx->text[ctx->i];
		op[1] = '\0';
		opd[0] = ctx->dna[ctx->i];
		opd[1] = '\0';
	}
	return (push_token(ctx->head, op, opd, ctx->trash), ctx->opflag);
}
