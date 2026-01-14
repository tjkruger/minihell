/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaraogl <hkaraogl@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 14:51:47 by hkaraogl          #+#    #+#             */
/*   Updated: 2026/01/14 14:56:52 by hkaraogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
