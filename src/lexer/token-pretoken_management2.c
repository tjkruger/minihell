/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token-pretoken_management2.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjkruger <tjkruger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 16:36:21 by tjkruger          #+#    #+#             */
/*   Updated: 2026/01/13 16:36:57 by tjkruger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	toggle_or_skip_quote(char **p, char *mode)
{
	if (*mode == 0)
		*mode = **p;
	else
		*mode = 0;
	(*p)++;
}

static void	append_one_char(char **p, char *tok, char *dna, int *i, char mode)
{
	tok[*i] = **p;
	dna[*i] = (mode == 0) ? 'N' : (mode == '\'') ? 'S' : 'D';
	(*i)++;
	(*p)++;
}

/* --- main extracted_token (short, delegates to helpers) --- */

static void	fill_token(char *str, char *end, char **pair)
{
	char	*p;
	int		i;
	char	mode;

	p = str;
	i = 0;
	mode = 0;
	while (p < end)
	{
		if ((*p == '"' || *p == '\'') && mode == 0 && *(p + 1) == *p)
		{
			handle_empty_quote_and_advance(&p, pair[1], &i);
			continue ;
		}
		if (((*p == '"' || *p == '\'') && mode == 0)
		|| (*p == mode && mode != 0))
		{
			toggle_or_skip_quote(&p, &mode);
			continue ;
		}
		append_one_char(&p, pair[0], pair[1], &i, mode);
	}
	pair[0][i] = '\0';
	pair[1][i] = '\0';
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
		if (end == NULL) /* unclosed quote */
			return (-1);
		count++;
		str = end;
	}
	return (count);
}