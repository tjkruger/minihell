/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_hkaraogl_3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaraogl <hkaraogl@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 18:03:29 by hkaraogl          #+#    #+#             */
/*   Updated: 2026/01/13 18:22:04 by hkaraogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	error_exit_perror(char *context, int code)
{
	ft_perror(context);
	return (code);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0')
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (s1[i] - s2[i]);
}

int	strncmp_strlen(char *s1, char *s2)
{
	int	str_len;

	str_len = ft_strlen(s1);
	return ((str_len == ft_strlen(s2)) && (ft_strncmp(s1, s2, str_len) == 0));
}

int	count_array_string(char **arr)
{
	int i = 0;

	while (arr[i])
		i++;
	return (i);
}