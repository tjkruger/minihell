/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjkruger <tjkruger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 15:32:25 by tjkruger          #+#    #+#             */
/*   Updated: 2026/01/13 16:26:29 by tjkruger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	token_length(char *str_start, char *str_end)
{
	int	length;

	length = (int)(str_end - str_start);
	return (length);
}


void	token_error(void)
{
	printf("please provide closing qoutes aswell would you ?\n");
}

char	*find_token_end(char *str)
{
	char	quote;

	while (str && *str && !ft_isspace(*str))
	{
		if (*str == '"' || *str == '\'')
		{
			quote = *str++;
			while (*str && *str != quote)
				str++;
			if (*str == '\0')
				return (NULL);
			str++;
		}
		else
			str++;
	}
	return (str);
}

static char	**make_token_pair(int len, t_trash *trash)
{
	char	**list;

	list = gc_malloc(trash, 3, sizeof(char *));
	if (!list)
		return (NULL);
	list[0] = gc_malloc(trash, len + 1, sizeof(char));
	list[1] = gc_malloc(trash, len + 1, sizeof(char));
	if (!list[0] || !list[1])
		return (NULL);
	list[2] = NULL;
	return (list);
}

static int	handle_empty_quote_and_advance(char **p, char *dna, int *i)
{
	dna[(*i)++] = 'Q';
	*p += 2;
	return (1);
}

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

t_pretoken	*allocate_pretoken(t_trash *trash, int arg_num)
{
	t_pretoken	*t_list;

	t_list = gc_malloc(trash, 1, sizeof(t_pretoken));
	if (!t_list)
		return (NULL);
	t_list->token = gc_malloc(trash, (arg_num + 1), sizeof(char *));
	t_list->dna = gc_malloc(trash, (arg_num + 1), sizeof(char *));
	if (!t_list->token || !t_list->dna)
		return (NULL);
	return (t_list);
}

int	fill_pretoken(t_pretoken *t_list, char *str, int arg_num, t_trash *trash)
{
	int		j;
	char	**pair;

	j = 0;
	while (*str && j < arg_num)
	{
		pair = extracted_token(str, trash);
		if (!pair)
			return (0);
		t_list->token[j] = pair[0];
		t_list->dna[j] = pair[1];
		str = find_token_end(str);
		while (*str && ft_isspace(*str))
			str++;
		j++;
	}
	t_list->token[j] = NULL;
	t_list->dna[j] = NULL;
	return (1);
}

t_pretoken	*ft_split_for_token(char *input, t_trash *trash)
{
	t_pretoken	*t_list;
	int			arg_num;

	arg_num = how_many_token(input);
	if (arg_num == -1)
	{
		token_error();
		return (NULL);
	}
	t_list = allocate_pretoken(trash, arg_num);
	if (!t_list)
		return (NULL);
	if (!fill_pretoken(t_list, input, arg_num, trash))
		return (NULL);
	return (t_list);
}
