/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_environment.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaraogl <hkaraogl@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 17:52:34 by hkaraogl          #+#    #+#             */
/*   Updated: 2026/01/13 18:08:55 by hkaraogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_environment_list(t_env_list *list)
{
	list->head = NULL;
	list->tail = NULL;
	list->size = 0;
	list->last_exit = 0;
}

t_env_list	*init_environment(char **system_env)
{
	t_env_list	*list;
	char		*equal;
	char		*key;
	char		*value;
	int			i;

	i = 0;
	list = malloc(sizeof(t_env_list));
	if (!list)
		return (NULL);
	init_environment_list(list);
	while (system_env[i])
	{
		equal = ft_strchr(system_env[i], '=');
		if (equal)
		{
			key = ft_substr(system_env[i], 0, equal - system_env[i]);
			value = ft_strdup(equal + 1);
			add_env_node(list, key, value, 1);
		}
		i++;
	}
	return (list);
}
