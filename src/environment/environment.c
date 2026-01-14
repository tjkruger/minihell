/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjkruger <tjkruger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 11:52:25 by hkaraogl          #+#    #+#             */
/*   Updated: 2026/01/14 15:44:51 by tjkruger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_exported_vars(t_env_list *env)
{
	t_env_node	*current;
	int			count;

	count = 0;
	current = env->head;
	while (current)
	{
		if (current->exported)
			count++;
		current = current->next;
	}
	return (count);
}

static char	*create_env_string(char *key, char *value)
{
	char	*str;
	int		len;

	len = ft_strlen(key) + ft_strlen(value);
	str = malloc(len + 2);
	if (!str)
		return (NULL);
	ft_strlcpy(str, key, len + 2);
	ft_strlcat(str, "=", len + 2);
	ft_strlcat(str, value, len + 2);
	return (str);
}

int	fill_env_array(char **arr, t_env_list *env)
{
	t_env_node	*current;
	int			i;

	i = 0;
	current = env->head;
	while (current)
	{
		if (current->exported)
		{
			arr[i] = create_env_string(current->key, current->value);
			if (!arr[i])
				return (0);
			i++;
		}
		current = current->next;
	}
	arr[i] = NULL;
	return (1);
}

char	*find_command_path(t_trash *trash, char *cmd)
{
	char	*path;
	char	**path_dirs;
	char	*full_path;
	int		i;
	char	*temp;

	i = 0;
	if (is_absolut_path(cmd))
		return (ft_strdup(cmd));
	path = getenv("PATH");
	path_dirs = gc_split(trash, path, ':');
	if (!path_dirs)
		return (NULL);
	while (path_dirs[i] != NULL)
	{
		temp = ft_strjoin(path_dirs[i], "/");
		full_path = ft_strjoin(temp, cmd);
		free(temp);
		if (access(full_path, X_OK) == 0)
			return (free_str_arr(path_dirs), full_path);
		free(full_path);
		i++;
	}
	return (free_str_arr(path_dirs), NULL);
}

void	add_env_node(t_env_list *env, char *key, char *value, int exported)
{
	t_env_node	*node;

	node = malloc(sizeof(t_env_node));
	if (!node)
		return ;
	node->key = key;
	node->value = value;
	node->exported = exported;
	node->next = NULL;
	if (!env->tail)
	{
		env->head = node;
		env->tail = node;
	}
	else
	{
		env->tail->next = node;
		env->tail = node;
	}
	env->size++;
}
