/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaraogl <hkaraogl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 13:04:23 by hkaraogl          #+#    #+#             */
/*   Updated: 2025/12/18 13:39:44 by hkaraogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int wait_all_children(t_pipes *data)
{
	int i;
	int status;
	int last_status;
	int last_signal;

	last_status = 0;
	last_signal = 0;
	i = 0;
	while (i < data->command_count)
	{
		waitpid(data->pids[i], &status, 0);
		if (WIFSIGNALED(status))
		{
			last_signal = WTERMSIG(status);
			last_status = 128 + last_signal;
		}
		else if (WIFEXITED(status))
			last_status = WEXITSTATUS(status);
		i++;
	}
	if (last_signal == SIGQUIT)
		write(STDOUT_FILENO, "Quit (core dumped)\n", 19);
	close_all_pipes(data);
	// free_pipes(data);
	return (setup_signals_interactive(), last_status);
}

// int wait_all_children(t_pipes *data)
// {
// 	int wait_status;
// 	int last_status;
// 	int i;
// 	int sig;

// 	i = 0;
// 	while(i < data->command_count)
// 	{
// 		waitpid(data->pids[i], &wait_status, 0);
// 		if(WIFSIGNALED(wait_status))
// 		{
// 			sig = WTERMSIG(wait_status);
// 			last_status = 128 + sig;
// 			if(sig == SIGQUIT)
// 				write(STDOUT_FILENO, "Quit (core dumped)\n", 19);		
// 		}
// 		else if(WIFEXITED(wait_status))
// 			last_status = WEXITSTATUS(wait_status);
// 		else
// 			last_status = 1;
// 		i++;
// 	}
// 	close_all_pipes(data);
// 	free_pipes(data);
// 	setup_signals_interactive();
// 	return last_status;
// }

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

void execute_child(t_trash *trash, t_one_command *cmd, t_pipes *data, t_env_list *env, int index)
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
		execute_external_command(trash, cmd, env);
}