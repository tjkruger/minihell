/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocate-fill_pretoken.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjkruger <tjkruger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 16:24:18 by tjkruger          #+#    #+#             */
/*   Updated: 2026/01/14 11:54:53 by tjkruger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
