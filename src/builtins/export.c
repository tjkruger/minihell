/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaraogl <hkaraogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 13:01:43 by hkaraogl          #+#    #+#             */
/*   Updated: 2025/11/11 15:16:32 by hkaraogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


//Es gibt Unterschiede zwischen export und env Builtin!!


static void sort_env(t_env_list *env)
{
	return;
}

//env must be sorted
static void print_export(t_env_list *env)
{
	t_env_node *current;

	current = env->head;

	while(current)
	{
		printf("declare -x %s=\"%s\"\n", current->key, current->value);
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
			set_env_value(env, key, value);
			free(key);
		}
		else
			set_env_value(env, cmd[i], "");
		i++;
	}
	return exit_code;
}
