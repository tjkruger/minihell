/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaraogl <hkaraogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 15:03:52 by hkaraogl          #+#    #+#             */
/*   Updated: 2025/10/28 19:47:58 by hkaraogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int fork_and_execute(char **cmd, char **envp)
{
	pid_t pid;
	int status;
	pid = fork();

	if(pid < 0)
	{
		perror("fork failed");
		return 1;
	}
	else if(pid == 0)
	{
		//child process
		execve(cmd[0], cmd, envp);
		perror("execve  failed");
		exit(127);
	}
	else
	{
		//pruefe wie Child beendet wurde
		waitpid(pid, &status, 0);
		if(WIFEXITED(status)) //normal beendet mit exit()
			return (WEXITSTATUS(status)); //extrahiere exit code (0 -255)
		if(WIFSIGNALED(status)) //durch Signal beendet (zB ctrol + C)
			return (128 + WTERMSIG(status)); //bash convention
	}
	return 0;
}

int execute_single_command(t_cmd_node *cmd, char **envp)
{
	//todo Buildin check
	//todo Redirection setup
	//todo: fork and exec
}

int execute_commands(t_cmd_list *cmd_list, char **envp)
{
	t_cmd_node *current;
	int status;

	if(!cmd_list || cmd_list->size == 0)
		return 0;
	
	current = cmd_list->head;
	
	//for now: 1 single cmd, later loop through all nodes
	status = execute_single_command(current, envp);
}
