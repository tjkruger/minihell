/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjkruger <tjkruger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 15:11:04 by tjkruger          #+#    #+#             */
/*   Updated: 2026/01/13 16:27:22 by tjkruger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"


char	*ft_argument(char *str, t_trash *trash)
{
    int		len;
    char	*var;

    if (!str || str[0] == '\0')
        return (gc_strdup(trash, ""));
    if (str[0] == '?')
        return (gc_strdup(trash, "?"));
    len = 0;
    while (str[len] && (isalnum((unsigned char)str[len]) || str[len] == '_'))
        len++;
    var = gc_malloc(trash, len + 1, sizeof(char));
    if (!var)
        return (NULL);
    strncpy(var, str, len);
    var[len] = '\0';
    return (var);
}

char	*ft_expand(char *arg, t_env_list *env)
{
    if (!arg)
        return (NULL);
    return (get_env_value(env, arg));
}

static int	calculate_result_len(char *str, char *new, int how_much)
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

static void	fill_result(char *result, char *str, char *new, int pos_in_str,
        int how_much)
{
    int	i;
    int	j;

    i = 0;
    j = 0;
    while (j < pos_in_str)
        result[i++] = str[j++];
    j = 0;
    while (new && new[j])
        result[i++] = new[j++];
    j = pos_in_str + how_much;
    while (str && str[j])
        result[i++] = str[j++];
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
    fill_result(result, ctx->str, ctx->replacement, ctx->pos, ctx->len);
    return (result);
}

char	*exit_state_to_str(int exit_state, t_trash *trash)
{
    return (gc_itoa(trash, exit_state));
}
static char	*get_expansion_string(char *arg, t_env_list *env, t_trash *trash)
{
    if (!arg)
        return (NULL);
    if (arg[0] == '?' && arg[1] == '\0')
        return (exit_state_to_str(env->last_exit, trash));
    return (ft_expand(arg, env));
}

static char	*insert_literal_dollar(char *str, int pos, t_trash *trash)
{
    t_expand_ctx	ctx;
    char			*new;

    ctx.trash = trash;
    ctx.str = str;
    ctx.replacement = "$";
    ctx.pos = pos;
    ctx.len = 1;
    new = insert_expandet(&ctx);
    return (new);
}

static int	process_expansion_at(t_token *token, int i, t_env_list *env,
        t_trash *trash)
{
    char		*arg;
    char		*ex_str;
    char		*new;
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
        ex_str = "";
    ctx.trash = trash;
    ctx.str = token->value;
    ctx.replacement = ex_str;
    ctx.pos = i;
    ctx.len = ft_strlen(arg) + 1;
    new = insert_expandet(&ctx);
    if (new)
        token->value = new;
    return (i + (int)ft_strlen(ex_str)); /* caller loop will ++, so this positions correctly */
}

void	handle_expansions(t_token *token_list, t_env_list *env, t_trash *trash)
{
    char	*str;
    int		i;

    while (token_list)
    {
        str = token_list->value;
        if (!str)
        {
            token_list = token_list->next;
            continue ;
        }
        i = 0;
        while (str[i])
        {
            if (str[i] == '$' && (!token_list->dna || token_list->dna[i] != 'S')
                && (!token_list->dna || token_list->dna[i + 1] != 'Q'))
            {
                i = process_expansion_at(token_list, i, env, trash);
                continue ;
            }
            i++;
        }
        token_list = token_list->next;
    }
}
