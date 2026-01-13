/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaraogl <hkaraogl@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 13:01:43 by hkaraogl          #+#    #+#             */
/*   Updated: 2026/01/13 15:37:01 by hkaraogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	swap_content(t_env_node *node1, t_env_node *node2)
{
	char	*tmp_key;
	char	*tmp_value;
	int		tmp_exported;

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

static void	print_export(t_env_list *env)
{
	t_env_node	*current;

	current = env->head;
	while (current)
	{
		if (current->exported && current->value)
			printf("declare -x %s=\"%s\"\n", current->key, current->value);
		else
			printf("declare -x %s\n", current->key);
		current = current->next;
	}
}

static int	export_with_value(t_env_list *env, char *arg, char *equal)
{
	char	*key;
	char	*value;

	key = ft_substr(arg, 0, equal - arg);
	if (!key)
		return (1);
	value = equal + 1;
	set_env_value(env, key, value, 1);
	free(key);
	return (0);
}

static int	process_export_arg(t_env_list *env, char *arg)
{
	char	*equal;

	if (!is_valid_identifier(arg))
	{
		print_export_error(arg);
		return (1);
	}
	equal = has_equal(arg);
	if (equal)
		return (export_with_value(env, arg, equal));
	else
		set_env_value(env, arg, NULL, 0);
	return (0);
}

int	run_export(t_env_list *env, char **cmd)
{
	int	i;
	int	exit_code;

	if (!cmd[1])
	{
		sort_env(env);
		print_export(env);
		return (0);
	}
	i = 1;
	exit_code = 0;
	while (cmd[i])
	{
		if (process_export_arg(env, cmd[i]) != 0)
			exit_code = 1;
		i++;
	}
	return (exit_code);
}
