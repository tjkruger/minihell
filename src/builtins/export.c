/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaraogl <hkaraogl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 13:01:43 by hkaraogl          #+#    #+#             */
/*   Updated: 2025/12/15 15:39:14 by hkaraogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


//Es gibt Unterschiede zwischen export und env Builtin!!


static void	swap_content(t_env_node *node1, t_env_node *node2)
{
	char *tmp_key;
	char *tmp_value;
	int tmp_exported;

	tmp_key = node1->key;
	tmp_value = node1->value;
	tmp_exported = node1->exported;

	node1->key = node2->key;
	node1->value = node2->value;
	node1->exported = node2->exported;

	node2->key = tmp_key;
	node2->value = tmp_value;
	node2->exported = tmp_exported;
}

//env must be sorted
static void sort_env(t_env_list *env)
{
	t_env_node *current;
	t_env_node *compare;
	char *tmp;

	current = env->head;

	while(current)
	{
		compare = current->next;
		while(compare)
		{
			if(ft_strcmp(current->key, compare->key) > 0)
				swap_content(current, compare);
			compare = compare->next;
		}
		current = current->next;
	}
}

static void print_export(t_env_list *env)
{
	t_env_node *current;

	current = env->head;
	while(current)
	{
		if(current->exported && current->value)
			printf("declare -x %s=\"%s\"\n", current->key, current->value);
		else
			printf("declare -x %s\n", current->key);
		current = current->next;
	}
}

int	run_export(t_env_list *env, char **cmd)
{
	int i = 1;
	int exit_code = 0;
	char *equal;
	char *key;
	char *value;
	if(!cmd[1])
	{
		sort_env(env);
		print_export(env);
		return 0;
	}
	while(cmd[i])
	{
		if(!is_valid_identifier(cmd[i]))
		{
			ft_putstr_fd("bash:", 1);
			ft_putstr_fd(cmd[i], 1);
			ft_putendl_fd("not a valid identifier", 1);
			exit_code = 1;
		}
		equal = has_equal(cmd[i]);
		if(equal)
		{
			key = ft_substr(cmd[i], 0, equal - cmd[i]);
			value = equal + 1;
			set_env_value(env, key, value, 1);
			free(key);
		}
		else
			set_env_value(env, cmd[i], NULL, 0);
		i++;
	}
	return exit_code;
}
