/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaraogl <hkaraogl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 15:03:52 by hkaraogl          #+#    #+#             */
/*   Updated: 2026/01/07 14:27:59 by hkaraogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int init_pipes(t_ms *ms, t_pipes *data)
{
	data->pipes = NULL;
	data->pids = NULL;
	data->command_count = ms->all_commands->size;
	data->pipe_count = ms->all_commands->size - 1;
	if(data->pipe_count > 0)
	{
		data->pipes = create_pipes(&ms->trash, data->pipe_count);
		if(!data->pipes)
			return 0;
	}
	data->pids = gc_malloc(&ms->trash, ms->all_commands->size, sizeof(pid_t));
	if(!data->pids)
		return 0;
	return 1;
}

int process_builtin(t_one_command *node, t_ms *ms)
{
	int status;

	status = 1;
	if(ft_strcmp(node->cmd[0], "cd") == 0)
		status = run_cd(node->cmd, ms->env_list);
	else if(ft_strcmp(node->cmd[0], "echo") == 0)
		status = run_echo(node);
	else if(ft_strcmp(node->cmd[0], "env") == 0)
		status = run_env(ms->env_list);
	else if(ft_strcmp(node->cmd[0], "exit") == 0)
		status = run_exit(ms);
	else if(ft_strcmp(node->cmd[0], "export") == 0)
		status = run_export(ms->env_list, node->cmd);
	else if(ft_strcmp(node->cmd[0], "pwd") == 0)
		status = run_pwd();
	else if(ft_strcmp(node->cmd[0], "unset") == 0)
		status = run_unset(node->cmd, ms->env_list);
	return status;
}

// backup fds, set redirections, execute builtin, restore fds
static int	execute_builtin(t_ms *ms, t_one_command *node)
{
	int status;
	int fd_backups[2];

	init_fd_backups(fd_backups);
	if(node->files && node->files->head)
	{
		backup_fds(fd_backups);
		if(fd_backups[0] == -1 || fd_backups[1] == -1)
			return 1;
		if(!set_redirections(node->files))
		{
			restore_fds(fd_backups);
			return 1;
		}
	}

	status = process_builtin(node, ms);
	if(node->files && node->files->head)
		restore_fds(fd_backups);
	return (status);
}

int get_exit_status(int status)
{
	if(WIFEXITED(status))
		return WEXITSTATUS(status);
	return 1;
}

int	execute_external_command(t_ms *ms, t_one_command *cmd)
{
	char **env;
	char *path;

	env = env_list_array(ms->env_list);
	path = find_command_path(&ms->trash, cmd->cmd[0]);
	if(!path)
	{
		print_cmd_error(cmd->cmd[0], "command not found");
		exit(ERR_CMD_NOT_FOUND);
	}
	execve(path, cmd->cmd, env);
	ft_perror("execve");
	exit(ERR_EXEC_FAIL);
}

static int	execute_with_pipes(t_ms *ms)
{
	t_pipes data;
	t_one_command *current;
	int i;

	if(!init_pipes(ms, &data))
		return (ft_perror("failed to initialize pipes"),1);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);

	
	i = 0;
	current = ms->all_commands->head;
	while(current)
	{
		data.pids[i] = fork();
		if(data.pids[i] == -1)
		{
			ft_perror("fork");
			close_all_pipes(&data);
			setup_signals_interactive();
			return 1;
		}
		if(data.pids[i] == 0)
		{
			setup_signals_child();
			execute_child(ms, current, &data, i);
		}
		current = current->next;
		i++;
	}
	int status;
	close_all_pipes(&data);
	status = wait_all_children(&data);
	setup_signals_interactive();
	return status;
}

int	execute_commands(t_ms *ms)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	t_one_command *current;

	if(!ms->all_commands || !ms->all_commands->head)
		return 1;
	current = ms->all_commands->head;

	if (ms->all_commands->size == 1 && current->cmd_type == BUILTIN)
	{
		int status;

		status = execute_builtin(ms, current);
		setup_signals_interactive();
		return status;
	}

	return execute_with_pipes(ms);
}
