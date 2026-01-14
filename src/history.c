/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjkruger <tjkruger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 15:33:50 by tjkruger          #+#    #+#             */
/*   Updated: 2026/01/14 15:33:54 by tjkruger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_empty_or_whitespace(const char *s)
{
	if (!s)
		return (1);
	while (*s)
	{
		if (!isspace((unsigned char)*s))
			return (0);
		s++;
	}
	return (1);
}

t_history	*add_to_hist_list(t_history **list, char *command_to_list)
{
	t_history	*entry;
	t_history	*tmp;

	entry = malloc(sizeof(t_history));
	if (!entry)
		return (NULL);
	entry->command = strdup(command_to_list);
	entry->next = NULL;
	if (*list == NULL)
		*list = entry;
	else
	{
		tmp = *list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = entry;
	}
	return (entry);
}

void	print_history(t_history *list)
{
	int	i;

	i = 1;
	while (list)
	{
		printf("%d  %s\n", i, list->command);
		list = list->next;
		i++;
	}
}
