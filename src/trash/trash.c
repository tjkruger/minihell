/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trash.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaraogl <hkaraogl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 16:43:31 by hkaraogl          #+#    #+#             */
/*   Updated: 2025/12/17 13:28:32 by hkaraogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void trash_init(t_trash *trash)
{
	trash->head = NULL;
	trash->tail = NULL;
	trash->size = 0;
}

void gc_add(t_trash *trash, void *ptr)
{
	t_trash_node *new_node;

	if(!trash || !ptr)
		return;
	new_node = malloc(sizeof(t_trash_node));
	if(!new_node)
	{
		free(ptr);
		ft_perror("gc_add: malloc failed");
		return;	
	}
	new_node->data = ptr;
	new_node->next = NULL;
	if(!trash->head)
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

void *gc_malloc(t_trash *trash, size_t count, size_t size)
{
	void *ptr;

	ptr = malloc(count * size);
	if(!ptr)
	{
		ft_perror("malloc failed");
		return NULL;
	}
	gc_add(trash, ptr);
	return ptr;
}

char *gc_strdup(t_trash *trash, const char *s1)
{
	int		len;
	int		count;
	char	*new_str;

	len = 0;
	count = 0;
	while (s1[len] != '\0')
		len++;
	new_str = (char *)gc_malloc(trash,len + 1, sizeof(char));
	if (new_str == 0)
	{
		return (0);
	}
	while (count < len)
	{
		new_str[count] = s1[count];
		count++;
	}
	new_str[len] = '\0';
	return (new_str);
}

char *gc_substr(t_trash *trash, const char *s, unsigned int start, size_t len)
{
	char	*temp;
	size_t	i;
	size_t	len_s;

	temp = NULL;
	i = 0;
	if (!s)
		return (NULL);
	len_s = ft_strlen(s);
	if (start >= len_s)
		return (ft_strdup(""));
	if (len > len_s - start)
		len = len_s - start;
	temp =gc_malloc(trash, len + 1,  sizeof(char));
	if (!temp)
		return (NULL);
	while (i < len)
	{
		temp[i] = s[start + i];
		i++;
	}
	temp[i] = '\0';
	return (temp);
}

void gc_cleanup(t_trash *trash)
{
	t_trash_node *current;
	t_trash_node *next;

	if (!trash)
		return;
	current = trash->head;
	while (current)
	{
		next = current->next;
		free(current->data);
		free(current);
		current = next;
	}
	trash->head = NULL;
	trash->tail = NULL;
	trash->size = 0;
}
