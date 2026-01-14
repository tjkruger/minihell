/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_helpers-checks.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjkruger <tjkruger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 16:25:17 by tjkruger          #+#    #+#             */
/*   Updated: 2026/01/14 12:03:13 by tjkruger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_op(char c)
{
	return (c == '>' || c == '<' || c == '|');
}

int	ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r')
		return (1);
	return (0);
}

int	is_specialchar(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

int	is_var_char(char c)
{
	return (c != '\0' && c != ' ' && c != '|' && c != '>' && c != '<'
		&& c != '$');
}

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
