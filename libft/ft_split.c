/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: r2d2 <r2d2@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 17:28:21 by tjkruger          #+#    #+#             */
/*   Updated: 2025/10/18 11:03:14 by r2d2             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// #include <stdlib.h>
// #include <stdio.h>

static int	wordcount(const char *s, char c)
{
	int i;
	int count;

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

static char	*worddup(const char *s, int start, int end)
{
	char *word;
	int i;

	i = 0;
	word = malloc((end - start + 1) * sizeof(char));
	if (!word)
		return (NULL);
	while (start < end)
		word[i++] = s[start++];
	word[i] = '\0';
	return (word);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	int		i;
	int		j;
	int		start;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	result = malloc((wordcount(s, c) + 1) * sizeof(char *));
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
			result[j++] = worddup(s, start, i);
	}
	result[j] = NULL;
	return (result);
}


// int	main(void)
// {
// 	char **result = ft_split("  hello there i got yo ass ", ' ');
// 	for (int i = 0; result[i] != NULL; i++)
// 		printf("|%s|\n", result[i]);
// }