/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaraogl <hkaraogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 11:52:25 by hkaraogl          #+#    #+#             */
/*   Updated: 2025/11/03 14:46:18 by hkaraogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//convert linkedlist to an array for execve which needs a **env
//**ret needs to be freed by user 
char **env_list_array(t_env_list *env)
{
	char **ret;
	char *tmp;
	int i = 0;
	t_env_node *current;
	int len;
	ret = malloc(sizeof(char *) * (env->size + 1));
	if(!ret)
		return NULL;
	current = env->head;
	while(current)
	{
		len = ft_strlen(current->key) + ft_strlen(current->value);
		ret[i] = malloc(len + 2);
		if(!ret[i])
			return NULL;
		ft_strlcpy(ret[i], current->key, len + 2);
		ft_strlcat(ret[i], "=", len + 2);
		ft_strlcat(ret[i], current->value, len + 2);
		current = current->next;
		i++;
	}
	ret[i] = NULL;
	return ret;
}

//delete a node which has char *key
int	unset_env_value(t_env_list *env, char *key)
{
	t_env_node	*prev;
	t_env_node	*current;

	current = env->head;
	prev = NULL;
	while (current)
	{
		if (strncmp_strlen(current->key, key))
		{
			if (prev)
				prev->next = current->next;
			else
				env->head = current->next;
			if (current == env->tail)
				env->tail = prev;
			free(current->key);
			free(current->value);
			free(current);
			env->size--;
			return (0);
		}
		prev = current;
		current = current->next;
	}
	return (0);
}

//add a note which has key and value to the end (tail)
int	set_env_value(t_env_list *env, char *key, char *value)
{
	t_env_node	*node;

	node = find_env_node(env, key);
	if (node)
	{
		free(node->value);
		node->value = ft_strdup(value);
		return (0);
	}
	add_env_node(env, ft_strdup(key), ft_strdup(value));
	return (0);
}
// bekomme env linked list und key
// returnt den value
// PWD=/home/hkaraogl/Core/Rank3/minishell
// zB key = "PWD"
// value = "/home/hkaraogl/Core/Rank3/minishell"
// falls Variable nicht im linkedlist ist, such im Sytem_ENV
// falls dort auch nicht, dann return (NULL);
char	*get_env_value(t_env_list *env, char *key)
{
	t_env_node	*node;

	node = find_env_node(env, key);
	if (node)
		return (node->value);
	return (getenv(key));
}

// bekommt die env Linkedlist und den Key
//
t_env_node	*find_env_node(t_env_list *env, char *key)
{
	t_env_node	*current;
	int			key_len;

	key_len = ft_strlen(key);
	current = env->head;
	while (current)
	{
		if (strncmp_strlen(current->key, key))
			return (current);
		current = current->next;
	}
	return (NULL);
}

// return 1 (true) when cmd has a '/' and access to the path
// example: /usr/bin/ls
// 0 (false) when no'/' and/or no access
// example: /usr/bin/none_existend
static int	is_absolut_path(char *cmd)
{
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (1);
	}
	return (0);
}

// cmd = "cat"
// **env =
// {
// USER=max
// HOME=/home/max
// PATH=/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin  <--- we need this
// SHELL=/bin/bash
// LANG=de_DE.UTF-8
// PWD=/home/max/projects
// EDITOR=vim
// TERM=xterm-256colo
// NULL
// }
// return "/usr/bin/cat" if cmd is valid || NULL if invalid cmd
char	*find_command_path(char *cmd, char **env)
{
	char	*path;
	char	**path_dirs;
	char	*full_path;
	int		i;
	char *temp;

	i = 0;
	if (is_absolut_path(cmd))
		return (ft_strdup(cmd));
	path = getenv("PATH");
	path_dirs = ft_split(path, ':');
	if(!path_dirs)
		return NULL;
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

void	add_env_node(t_env_list *env, char *key, char *value)
{
	t_env_node	*node;

	node = malloc(sizeof(t_env_node));
	if (!node)
		return ;
	node->key = key;
	node->value = value;
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
	list->head = NULL;
	list->tail = NULL;
	list->size = 0;
	while (system_env[i])
	{
		equal = ft_strchr(system_env[i], '=');
		if (equal)
		{
			key = ft_substr(system_env[i], 0, equal - system_env[i]);
			value = ft_strdup(equal + 1);
			add_env_node(list, key, value);
		}
		i++;
	}
	return (list);
}
