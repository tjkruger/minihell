/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaraogl <hkaraogl@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 12:47:24 by hkaraogl          #+#    #+#             */
/*   Updated: 2026/01/14 16:11:03 by hkaraogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	wordcount(char *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
		{
			count++;
			while (s[i] && s[i] != c)
				i++;
		}
	}
	return (count);
}

static char	*worddup(t_trash *trash, char *s, int start, int end)
{
	char	*word;
	int		i;

	i = 0;
	word = gc_malloc(trash, (end - start + 1), sizeof(char));
	if (!word)
		return (NULL);
	while (start < end)
		word[i++] = s[start++];
	word[i] = '\0';
	return (word);
}

char	**gc_split(t_trash *trash, char *s, char c)
{
	char	**result;
	int		i;
	int		j;
	int		start;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	result = gc_malloc(trash, (wordcount(s, c) + 1), sizeof(char *));
	if (!result)
		return (NULL);
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		start = i;
		while (s[i] && s[i] != c)
			i++;
		if (i > start)
			result[j++] = worddup(trash, s, start, i);
	}
	result[j] = NULL;
	return (result);
}

void	gc_cleanup(t_trash *trash)
{
	t_trash_node	*current;
	t_trash_node	*next;

	if (!trash)
		return ;
	current = trash->head;
	while (current)
	{
		next = current->next;
		if (current->data)
			free(current->data);
		free(current);
		current = next;
	}
	trash->head = NULL;
	trash->tail = NULL;
	trash->size = 0;
}
