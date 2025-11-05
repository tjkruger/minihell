/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_hkaraogl.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaraogl <hkaraogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 13:40:50 by hkaraogl          #+#    #+#             */
/*   Updated: 2025/11/04 15:27:44 by hkaraogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include    "minishell.h"

int	strncmp_strlen(char *s1, char *s2)
{
	int str_len = ft_strlen(s1);
	return ((str_len == ft_strlen(s2)) && (ft_strncmp(s1, s2, str_len) == 0));
}

int count_array_string(char **arr)
{
	int i = 0;

	while(arr[i])
		i++;
	return i;
}

void	free_str_arr(char **arr)
{
	int i;

	i = 0;
	while(arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

int	is_valid_identifier(char *str)
{
	int i;

	if (!str || !str[0])
		return (0);
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	i = 1;
	while (str[i])
	{
		if (!ft_isalnum(str[i] && str[i] != '_'))
			return (0);
		i++;
	}
	return (1);
}