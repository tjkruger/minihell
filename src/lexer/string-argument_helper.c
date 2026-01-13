/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string-argument_helper.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjkruger <tjkruger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 16:28:35 by tjkruger          #+#    #+#             */
/*   Updated: 2026/01/13 16:30:59 by tjkruger         ###   ########.fr       */
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