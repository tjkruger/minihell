/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token-pretoken_management2.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjkruger <tjkruger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 16:36:21 by tjkruger          #+#    #+#             */
/*   Updated: 2026/01/14 13:47:27 by tjkruger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	toggle_or_skip_quote(char **p, char *mode)
{
	if (*mode == 0)
		*mode = **p;
	else
		*mode = 0;
	(*p)++;
}

void	append_char_to_ctx(t_token_ctx *ctx)
{
	ctx->tok[ctx->i] = *ctx->p;
	if (ctx->mode == 0)
		ctx->dna[ctx->i] = 'N';
	else if (ctx->mode == '\'')
		ctx->dna[ctx->i] = 'S';
	else
		ctx->dna[ctx->i] = 'D';
	ctx->i++;
	ctx->p++;
}

int	handle_empty_quote(t_token_ctx *ctx)
{
	ctx->dna[ctx->i++] = 'Q';
	ctx->p += 2;
	return (1);
}

/* --- main extracted_token (short, delegates to helpers) --- */

void	fill_token(char *str, char *end, char **pair)
{
	t_token_ctx	ctx;

	ctx.p = str;
	ctx.tok = pair[0];
	ctx.dna = pair[1];
	ctx.i = 0;
	ctx.mode = 0;
	while (ctx.p < end)
	{
		if ((*ctx.p == '"' || *ctx.p == '\'')
			&& ctx.mode == 0 && *(ctx.p + 1) == *ctx.p)
		{
			handle_empty_quote(&ctx);
			continue ;
		}
		if (((*ctx.p == '"' || *ctx.p == '\'') && ctx.mode == 0)
			|| (*ctx.p == ctx.mode && ctx.mode != 0))
		{
			toggle_or_skip_quote(&ctx.p, &ctx.mode);
			continue ;
		}
		append_char_to_ctx(&ctx);
	}
	ctx.tok[ctx.i] = '\0';
	ctx.dna[ctx.i] = '\0';
}

char	**extracted_token(char *str, t_trash *trash)
{
	char	*end;
	char	**pair;
	int		len;

	end = find_token_end(str);
	if (!end)
		return (NULL);
	len = token_length(str, end);
	pair = make_token_pair(len, trash);
	if (!pair)
		return (NULL);
	fill_token(str, end, pair);
	return (pair);
}
