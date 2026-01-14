/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaraogl <hkaraogl@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 16:25:12 by hkaraogl          #+#    #+#             */
/*   Updated: 2026/01/14 16:10:32 by hkaraogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_len(int n)
{
	int	length;

	length = 0;
	if (n <= 0)
		length = 1;
	while (n != 0)
	{
		length++;
		n /= 10;
	}
	return (length);
}

char	*gc_itoa(t_trash *trash, int n)
{
	int		lengh;
	char	*result;
	int		is_neg;

	if (n == -2147483648)
		return (gc_strdup(trash, "-2147483648"));
	lengh = get_len(n);
	result = (char *)gc_malloc(trash, (lengh + 1), sizeof(char));
	if (!result)
		return (NULL);
	is_neg = (n < 0);
	if (is_neg)
		n = -n;
	result[lengh] = '\0';
	while (lengh > 0)
	{
		lengh--;
		result[lengh] = (n % 10) + '0';
		n /= 10;
	}
	if (is_neg)
		result[0] = '-';
	return (result);
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
