/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaraogl <hkaraogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 15:03:52 by hkaraogl          #+#    #+#             */
/*   Updated: 2025/11/10 18:34:32 by hkaraogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Validierung
//cmd_lst leer?
//sind cmds NULL?

void	(execute_builtin(t_cmd_node *cmd, t_env_list *env_lst))
{
	return;
}

void	execute_with_pipes(t_cmd_list *cmd_lst, t_env_list *env_lst)
{
	return;
}

void	execute_pipeline(t_cmd_list *cmd_lst, t_env_list *env_lst)
{
	t_cmd_node *current;
	
	current = cmd_lst->head;

	if(cmd_lst->size == 1 && current->cmd_type == BUILTIN)
	{
		execute_builtin(current, env_lst);
		return;
	}
	execute_with_pipes(cmd_lst, env_lst);
}

