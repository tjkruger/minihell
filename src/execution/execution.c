/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaraogl <hkaraogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 15:03:52 by hkaraogl          #+#    #+#             */
/*   Updated: 2025/11/19 17:41:58 by hkaraogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Validierung
//cmd_lst leer?
//sind cmds NULL?

// FD MANAGMENT REGEL:                                  ║
// ║                                                        ║
// ║  Jeder Prozess schließt:                              ║
// ║  1. Alle Pipe-Enden die er NICHT benutzt             ║
// ║  2. Die Pipe-Enden die er benutzt NACH dup2()        ║
// ║                                                        ║
// ║  Timing ist kritisch:                                 ║
// ║  - Children: Nach dup2(), vor execve()                ║
// ║  - Parent: Nach allen forks(), vor waitpid()  



int **create_pipes(int count)
{
	//Allokation
	//pipe erstellen
	//cleanup bei fehler
	//
}

void close_all_pipes(int **pipes, int count)
{
	//close(pipes[i][0])
	//close(pipes[i][i])
}

void	free_pipes(int **pipes, int count)
{
	int i = 0;

	if(!pipes)
		return;
	while(i < count)
	{
		free(pipes[i]);
		i++;
	}
	free(pipes);
}

int backup_fd(int fd)
{
	int backup;
	backup = dup(fd);
	if(backup == -1)
	{
		perror("dup");
		return -1;
	}
	return backup;
}

void restore_fd(int fd, int backup)
{
	dup2(backup, fd);
	close(backup);
}

void close_fd(int fd)
{
	if(close(fd) == -1)
	{
		perror("close");
	}
}



static int	execute_builtin(t_cmd_node *node, t_env_list *env_lst)
{
	int status;
	// set_redirection();
	if(ft_strcmp(node->cmd[0], "cd") == 0)
		status = run_cd(node->cmd, env_lst);
	else if(ft_strcmp(node->cmd[0], "echo") == 0)
		status = run_echo(node);
	else if(ft_strcmp(node->cmd[0], "env") == 0)
		status = run_env(env_lst);
	else if(ft_strcmp(node->cmd[0], "exit") == 0)
		status = run_exit(node->cmd, 1);
	else if(ft_strcmp(node->cmd[0], "export") == 0)
		status = run_export(env_lst, node->cmd);
	else if(ft_strcmp(node->cmd[0], "pwd") == 0)
		status = run_pwd();
	else if(ft_strcmp(node->cmd[0], "unset") == 0)
		status = run_unset(node->cmd, env_lst);
	return status;
}

int execute_pipeline(t_cmd_list *cmd_list, t_env_list *env_list)
{

	return 0;
}




int wait_process(int pid)
{
	int status;
	waitpid(pid, &status, 0);
	if(WIFEXITED(status))
		return WEXITSTATUS(status);
	return 1;
}

int	execute_with_pipes(t_cmd_list *cmd_lst, t_env_list *env_lst)
{

	return;
}

static int	execute_external_command(t_cmd_list *cmd_lst, t_env_list *env_lst)
{
	int status;
	char **env;
	t_cmd_node *cmd;
	char *path;
	pid_t pid;

	cmd = cmd_lst->head;
	path = find_command_path(cmd->cmd[0], env);
	if(!path)
	{
		ft_putstr_fd("minishell: command nout found", 2);
		ft_putendl_fd(cmd->cmd[0], 2);
		return 127;
	}
	pid = fork();
	if(pid == -1)
	{
		perror("fork");
		free(path);
		return 1;
	}
	if(pid == 0)
	{
		env = env_list_array(env_lst);
		execve(path, cmd->cmd, env);
		perror("execve");
		return 126;
	}
	free(path);
	return (wait_process(pid));
}

static int	execute_single_command(t_cmd_list *cmd_lst, t_env_list *env_lst)
{
	t_cmd_node *current;
	current = cmd_lst->head;
	if(current->cmd_type)//BUILTIN
	{
		return execute_builtin(current, env_lst);
	}
	else
		return execute_external_command(cmd_lst, env_lst);
}

int	execute_commands(t_cmd_list *cmd_lst, t_env_list *env_lst)
{
	t_cmd_node *current;

	if(!cmd_lst || !cmd_lst->head)
		return 1;
	
	current = cmd_lst->head;

	if(cmd_lst->size == 1)
		return execute_single_command(current, env_lst);

	return execute_with_pipes(cmd_lst, env_lst);
}
