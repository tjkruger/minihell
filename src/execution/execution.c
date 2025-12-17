/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaraogl <hkaraogl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 15:03:52 by hkaraogl          #+#    #+#             */
/*   Updated: 2025/12/16 15:24:36 by hkaraogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int init_pipes(t_pipes *data, t_all_commands *lst)
{
	data->pipes = NULL;
	data->pids = NULL;
	data->command_count = lst->size;
	data->pipe_count = lst->size - 1;
	if(data->pipe_count > 0)
	{
		data->pipes = create_pipes(data->pipe_count);
		if(!data->pipes)
			return 0;
	}

	data->pids = malloc(sizeof(pid_t) * lst->size);
	if(!data->pids)
	{
		free_pipes(data);
		return 0;
	}
	return 1;
}

int process_builtin(t_one_command *node, t_env_list *env_lst)
{
	int status;

	status = 1;
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

// backup fds, set redirections, execute builtin, restore fds
static int	execute_builtin(t_one_command *node, t_env_list *env_lst)
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

	status = process_builtin(node, env_lst);
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

int	execute_external_command(t_one_command *cmd, t_env_list *env_lst)
{
	char **env;
	char *path;

	env = env_list_array(env_lst);
	path = find_command_path(cmd->cmd[0]);
	if(!path)
	{
		print_cmd_error(cmd->cmd[0], "command not found");
		exit(ERR_CMD_NOT_FOUND);
	}
	execve(path, cmd->cmd, env);
	ft_perror("execve");
	free(path);
	exit(ERR_EXEC_FAIL);
}

static int	execute_with_pipes(t_all_commands *cmd_lst, t_env_list *env_lst)
{
	t_pipes data;
	t_one_command *current;
	int i;

	if(!init_pipes(&data, cmd_lst))
		return (ft_perror("failed to initialize pipes"),1);

	
	setup_signals_interactive();
	i = 0;
	current = cmd_lst->head;
	while(current)
	{
		data.pids[i] = fork();
		if(data.pids[i] == -1)
		{
			ft_perror("fork");
			close_all_pipes(&data);
			setup_signals_interactive();
			return (free_pipes(&data),1);
		}
		if(data.pids[i] == 0)
		{
			setup_signals_child();
			execute_child(current, &data, env_lst, i);
		}
		current = current->next;
		i++;
	}
	return wait_all_children(&data);
}

int	execute_commands(t_all_commands *cmd_lst, t_env_list *env_lst)
{
	t_one_command *current;

	if(!cmd_lst || !cmd_lst->head)
		return 1;
	current = cmd_lst->head;

	if(cmd_lst->size == 1 && current->cmd_type == BUILTIN)
		return execute_builtin(current, env_lst);

	return execute_with_pipes(cmd_lst, env_lst);
}
