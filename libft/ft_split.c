/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: r2d2 <r2d2@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 17:28:21 by tjkruger          #+#    #+#             */
/*   Updated: 2025/10/09 14:41:06 by r2d2             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	ft_count_words(const char *s, char c)
{
	int	in_word;
	int	count;

	in_word = 0;
	count = 0;
	while (*s)
	{
		if (*s != c && !in_word)
		{
			in_word = 1;
			count++;
		}
		else if (*s == c)
			in_word = 0;
		s++;
	}
	return (count);
}

static int	ft_wordcount_allocate(char ***result, const char *s, char c)
{
	int	count;

	if (s[0] == '\0')
	{
		*result = (char **)malloc(sizeof(char *));
		if (*result == NULL)
			return (0);
		(*result)[0] = NULL;
		return (1);
	}
	count = ft_count_words(s, c);
	*result = (char **)malloc((count + 1) * sizeof(char *));
	if (*result == NULL)
		return (0);
	return (count);
}

static void	ft_free_array(char **array, int elements)
{
	while (elements-- > 0)
		free(array[elements]);
	free(array);
}

static int	ft_copy_words(char **result, const char *s, char c)
{
	int	word_len;
	int	i;

	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			word_len = 0;
			while (s[word_len] && s[word_len] != c)
				word_len++;
			result[i] = (char *)ft_calloc(word_len + 1, 1);
			if (!result[i])
				return (ft_free_array(result, i), 0);
			ft_strlcpy(result[i], s, word_len + 1);
			i++;
			s += word_len;
		}
		else
			s++;
	}
	result[i] = NULL;
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	int		wordcount;

	if (!s)
		return (NULL);
	wordcount = ft_wordcount_allocate(&result, s, c);
	if (!result)
		return (NULL);
	if (!ft_copy_words(result, s, c))
		return (NULL);
	return (result);
}

// #include <stdlib.h>
// #include <string.h>

// char	**split(const char *str, const char *delimiter, int *count)
// {
// 	char	*token;
// 	char	**result;
// 	char	*temp;

// 	temp = strdup(str);
// 	// Duplicate the string to avoid modifying the original
// 	if (temp == NULL)
// 	{
// 		return (NULL); // Handle memory allocation failure
// 	}
// 	result = NULL;
// 	*count = 0;
// 	token = strtok(temp, delimiter);
// 	while (token != NULL)
// 	{
// 		result = realloc(result, (*count + 1) * sizeof(char *)); // Resize array
// 		if (result == NULL)
// 		{
// 			free(temp);
// 			return (NULL); // Handle memory allocation failure
// 		}
// 		result[*count] = strdup(token); // Duplicate the token
// 		(*count)++;
// 		token = strtok(NULL, delimiter);
// 	}
// 	free(temp);      // Free the temporary string
// 	return (result); // Return the array of tokens
// }

// int	main(void)
// {
// 	char **result = ft_split("           ", ' ');
// 	// for (int i = 0; result[i] != NULL; i++)
// 	// 	printf("|%s|", result[i]);
// }