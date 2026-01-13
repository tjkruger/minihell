/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaraogl <hkaraogl@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 17:46:47 by hkaraogl          #+#    #+#             */
/*   Updated: 2026/01/13 17:47:41 by hkaraogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include    "minishell.h"

char **env_list_array(t_env_list *env)
{
	char **ret;
	int count;

	count = count_exported_vars(env);
	ret = malloc(sizeof(char *) * (count + 1));
	if (!ret)
		return (NULL);
	if (!fill_env_array(ret, env))
	{
		free_str_arr(ret);
		return (NULL);
	}
	
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
int	set_env_value(t_env_list *env, char *key, char *value, int exported)
{
	t_env_node	*node;

	node = find_env_node(env, key);
	if (node)
	{
		if(exported)
		{
			free(node->value);
			node->value = ft_strdup(value);
			node->exported = 1;
		}
		return (0);
	}
	if(exported)
		add_env_node(env, ft_strdup(key), ft_strdup(value), 1);
	else
		add_env_node(env, ft_strdup(key), NULL, 0);
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