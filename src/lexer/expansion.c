/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjkruger <tjkruger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 16:31:35 by tjkruger          #+#    #+#             */
/*   Updated: 2026/01/15 14:23:35 by tjkruger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	calculate_result_len(char *str, char *new, int how_much)
{
	int	str_len;
	int	new_len;

	str_len = 0;
	while (str && str[str_len])
		str_len++;
	new_len = 0;
	while (new && new[new_len])
		new_len++;
	return (str_len - how_much + new_len);
}

void	fill_result(char *result, t_expand_ctx *ctx)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (j < ctx->pos)
		result[i++] = ctx->str[j++];
	j = 0;
	while (ctx->replacement && ctx->replacement[j])
		result[i++] = ctx->replacement[j++];
	j = ctx->pos + ctx->len;
	while (ctx->str && ctx->str[j])
		result[i++] = ctx->str[j++];
	result[i] = '\0';
}

char	*insert_expandet(t_expand_ctx *ctx)
{
	char	*result;
	int		result_len;

	if (!ctx || !ctx->str || !ctx->replacement || ctx->pos < 0)
		return (NULL);
	result_len = calculate_result_len(ctx->str, ctx->replacement, ctx->len);
	result = gc_malloc(ctx->trash, result_len + 1, sizeof(char));
	if (!result)
		return (NULL);
	fill_result(result, ctx);
	return (result);
}

int	process_expansion_at(t_token *token, int i, t_env_list *env, t_trash *trash)
{
	char			*arg;
	char			*ex_str;
	char			*new;
	t_expand_ctx	ctx;

	arg = ft_argument(token->value + i + 1, trash);
	if (!arg || arg[0] == '\0')
	{
		new = insert_literal_dollar(token->value, i, trash);
		if (new)
			token->value = new;
		return (i + 1);
	}
	ex_str = get_expansion_string(arg, env, trash);
	if (!ex_str)
		return (i + ft_strlen(arg) + 1);
	ctx.trash = trash;
	ctx.str = token->value;
	ctx.replacement = ex_str;
	ctx.pos = i;
	ctx.len = ft_strlen(arg) + 1;
	new = insert_expandet(&ctx);
	if (new)
		token->value = new;
	return (i + (int)ft_strlen(ex_str));
}

void	handle_expansions(t_token *tok_list, t_env_list *env, t_trash *trash)
{
	char	*str;
	int		i;

	while (tok_list)
	{
		str = tok_list->value;
		if (!str)
		{
			tok_list = tok_list->next;
			continue ;
		}
		i = 0;
		while (str[i])
		{
			if (str[i] == '$' && (!tok_list->dna || tok_list->dna[i] != 'S')
				&& (str[i + 1] && tok_list->dna[i + 1] != 'S'))
			{
				i = process_expansion_at(tok_list, i, env, trash);
				continue ;
			}
			i++;
		}
		tok_list = tok_list->next;
	}
}
