/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token-pretoken_management.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaraogl <hkaraogl@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 16:35:42 by tjkruger          #+#    #+#             */
/*   Updated: 2026/01/14 17:53:58 by hkaraogl         ###   ########.fr       */
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

char	**make_token_pair(int len, t_trash *trash)
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

int	handle_empty_quote_and_advance(char **p, char *dna, int *i)
{
	dna[(*i)++] = 'Q';
	*p += 2;
	return (1);
}
