/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaraogl <hkaraogl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 13:04:23 by hkaraogl          #+#    #+#             */
/*   Updated: 2025/12/02 13:06:15 by hkaraogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int wait_all_children(t_pipes *data)
{
	int status;
	int wait_status;
	int i;

	close_all_pipes(data);
	status = 0;
	i = 0;

	while(i < data->command_count)
	{
		waitpid(data->pids[i], &wait_status, 0);
		if(i == data->command_count - 1)
		{
			status = get_exit_status(wait_status);
		}
		i++;
	}
	free_pipes(data);
	return status;
}

//for single command: no use of dup2
void setup_child_pipes(t_pipes *data, int index)
{

	if(index > 0)
	{
		if(dup2(data->pipes[index - 1][0], STDIN_FILENO) == -1)
		{
			ft_perror("dup2");
			exit(1);
		}
	}
	if(index < data->pipe_count)
	{
		if(dup2(data->pipes[index][1], STDOUT_FILENO) == -1)
		{
			ft_perror("dup2");
			exit(1);
		}
	}
	
}

void execute_child(t_one_command *cmd, t_pipes *data, t_env_list *env, int index)
{
	setup_child_pipes(data, index);
	close_all_pipes(data);
	if(cmd->files && cmd->files->head)
	{
		if(!set_redirections(cmd->files))
			exit(1);
	}
	if(cmd->cmd_type == BUILTIN)
		exit(process_builtin(cmd, env));
	else
		execute_external_command(cmd, env);
}