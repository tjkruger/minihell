/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trash.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaraogl <hkaraogl@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 16:43:31 by hkaraogl          #+#    #+#             */
/*   Updated: 2026/01/14 15:00:57 by hkaraogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	trash_init(t_trash *trash)
{
	if (!trash)
		return ;
	trash->head = NULL;
	trash->tail = NULL;
	trash->size = 0;
}

/* add pointer to GC list; safe if trash is NULL (just don't track) */
void	gc_add(t_trash *trash, void *ptr)
{
	t_trash_node	*new_node;

	if (!ptr || !trash)
		return ;
	new_node = malloc(sizeof(t_trash_node));
	if (!new_node)
	{
		free(ptr);
		perror("gc_add: malloc failed");
		return ;
	}
	new_node->data = ptr;
	new_node->next = NULL;
	if (!trash->head)
	{
		trash->head = new_node;
		trash->tail = new_node;
	}
	else
	{
		trash->tail->next = new_node;
		trash->tail = new_node;
	}
	trash->size++;
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

void	gc_print(t_trash *trash)
{
	t_trash_node	*current;
	size_t			index;

	index = 0;
	if (!trash)
		return ;
	current = trash->head;
	printf("Garbage Collector Contents (size: %zd):\n", trash->size);
	while (current)
	{
		printf(" [%zu]: %p\n", index, current->data);
		current = current->next;
		index++;
	}
}

char	*gc_strjoin(t_trash *trash, char const *s1, char const *s2)
{
	size_t	len1;
	size_t	len2;
	char	*out;
	size_t	i;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	out = gc_malloc(trash, len1 + len2 + 1, sizeof(char));
	if (!out)
		return (NULL);
	i = 0;
	if (len1)
	{
		ft_memcpy(out + i, s1, len1);
		i += len1;
	}
	if (len2)
	{
		ft_memcpy(out + i, s2, len2);
		i += len2;
	}
	out[i] = '\0';
	return (out);
}
