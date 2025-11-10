/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaraogl <hkaraogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 13:01:43 by hkaraogl          #+#    #+#             */
/*   Updated: 2025/11/10 12:17:36 by hkaraogl         ###   ########.fr       */
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
	int exit_code = 0;;
	if(!cmd[1])
	{
		print_export(env);
		return 0;
	}

	while(cmd[i])
	{
		if(is_valid_identifier(cmd[i]))
		{
			set_env_value(env, cmd[i], "");
		}
		else
		{
			ft_putstr_fd("bash:", 1);
			ft_putstr_fd(cmd[i], 1);
			ft_putendl_fd("not a valid identifier", 1);
			exit_code = 1;
		}
		i++;
	}
	

}
