/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trash.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaraogl <hkaraogl@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 16:43:31 by hkaraogl          #+#    #+#             */
/*   Updated: 2026/01/13 18:41:55 by hkaraogl         ###   ########.fr       */
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

	if (!ptr)
		return ;
	if (!trash)
		return ; /* not tracking if trash is NULL */
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

void	*gc_malloc(t_trash *trash, size_t count, size_t size)
{
	void	*ptr;

	if (count == 0 || size == 0)
		return (NULL);
	ptr = malloc(count * size);
	if (!ptr)
	{
		perror("malloc failed");
		return (NULL);
	}
	gc_add(trash, ptr);
	return (ptr);
}

char	*gc_strdup(t_trash *trash, const char *s1)
{
	size_t	len;
	char	*new_str;

	if (!s1)
	{
		/* return empty string tracked by GC */
		new_str = gc_malloc(trash, 1, sizeof(char));
		if (!new_str)
			return (NULL);
		new_str[0] = '\0';
		return (new_str);
	}
	len = ft_strlen(s1);
	new_str = gc_malloc(trash, len + 1, sizeof(char));
	if (!new_str)
		return (NULL);
	ft_memcpy(new_str, s1, len);
	new_str[len] = '\0';
	return (new_str);
}

char	*gc_substr(t_trash *trash, const char *s, unsigned int start,
		size_t len)
{
	char	*temp;
	size_t	len_s;

	if (!s)
		return (gc_strdup(trash, ""));
	len_s = ft_strlen(s);
	if (start >= len_s)
		return (gc_strdup(trash, ""));
	if (len > len_s - start)
		len = len_s - start;
	temp = gc_malloc(trash, len + 1, sizeof(char));
	if (!temp)
		return (NULL);
	ft_memcpy(temp, s + start, len);
	temp[len] = '\0';
	return (temp);
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
	size_t len1;
	size_t len2;
	char *out;
	size_t i;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	out = gc_malloc(trash, len1 + len2 + 1, sizeof(char));
	if (!out)
		return (NULL);
	i = 0;
	if (len1)
		ft_memcpy(out + i, s1, len1), i += len1;
	if (len2)
		ft_memcpy(out + i, s2, len2), i += len2;
	out[i] = '\0';
	return (out);
}
