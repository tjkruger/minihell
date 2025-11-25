/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaraogl <hkaraogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 15:03:52 by hkaraogl          #+#    #+#             */
/*   Updated: 2025/11/25 18:16:32 by hkaraogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	free_pipes(t_pipes *data)
{
	int i = 0;

	if(!data->pipes)
		return;

	while(i < data->pipe_count)
	{
		free(data->pipes[i]);
		i++;
	}
	free(data->pipes);
	free(data->pids);

}

int	close_all_pipes(t_pipes *data)
{
	int i = 0;

	while(i < data->pipe_count)
	{
		close(data->pipes[i][0]);
		close(data->pipes[i][1]);
		i++;
	}
	return 0;
}

//creates pipes array
//exaample: pipes[0] = [read0, write0], pipes[1] = [read1, write1], 
int **create_pipes(int count)
{
	int **pipes;
	int i = 0;
	pipes = malloc(count * sizeof(int *));
	if(!pipes)
		return NULL;
	while(i < count)
	{
		pipes[i] = malloc(2 * sizeof(int));
		if(!pipes[i])
		{
			//cleanup free(pipes)
			return NULL;
		}
		if(pipe(pipes[i]) == -1)
		{
			perror("pipe");
			//cleanup
			return NULL;
		}
		i++;
	}
	return pipes;

}

// void	setup_pipe_fds(t_pipes *data, int index)
// {
// 	if(index > 0)
// 	{
// 		if(dup2(data->pipes[index -1][0], STDIN_FILENO) == -1)
// 		{

// 		}
// 	}
// }

//0 false, 1 true
int init_pipes(t_pipes *data, t_cmd_list *lst)
{
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

pid_t	fork_and_execute(t_cmd_node *cmd, t_pipes *data, t_env_list *env)
{
	pid_t pid;

	pid = fork();
	if(pid == -1)
	{
		perror("fork");
		return -1; //welchen return Wert?
	}
	if(pid == 0)
	{
		// setup_pipe_fds(data, index);
		close_all_pipes(data);
		set_redirections(cmd->files);
		execute_commands(cmd, env);
		exit(1);
	}
	return pid;
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

int wait_process(int pid)
{
	int status;
	waitpid(pid, &status, 0);
	if(WIFEXITED(status))
		return WEXITSTATUS(status);
	return 1;
}

static int get_exit_status(int status)
{
	if(WIFEXITED(status))
		return WEXITSTATUS(status);
	return 1;
}

static int wait_all_children(t_pipes *data)
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

static void setup_child_pipes(t_pipes *data, int index)
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

static void execute_child(t_cmd_node *cmd, t_pipes *data, t_env_list *env, int index)
{
	setup_child_pipes(data, index);
	close_all_pipes(data);
	if(cmd->files && cmd->files->head)
	{
		if(!set_redirections(cmd->files->head))
			exit(1);
	}
	if(cmd->cmd_type == BUILTIN)
		exit(execute_builtin(cmd, env));
	else
		execute_external_command(cmd, env);
}

int	execute_with_pipes(t_cmd_list *cmd_lst, t_env_list *env_lst)
{
	t_pipes data;
	t_cmd_node *current;
	int i;

	if(!init_pipes(&data, cmd_lst))
		return (ft_perror("failed to initialize pipes"),1);

	i = 0;
	current = cmd_lst->head;
	while(current)
	{
		data.pids[i] = fork();
		{
			ft_perror("fork");
			close_all_pipes(&data);
			return (free_pipes(&data),1);
		}
		if(data.pipes[i] == 0)
			execute_child(current, &data, env_lst, i);
		current = current->next;
		i++;
	}
	return (wait_all_children(&data));
}

static int	execute_external_command(t_cmd_list *cmd_lst, t_env_list *env_lst)
{
	char **env;
	t_cmd_node *cmd;
	char *path;

	cmd = cmd_lst->head;
	env = env_list_array(env_lst);
	path = find_command_path(cmd->cmd[0], env);
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

static int	execute_single_command(t_cmd_list *cmd_lst, t_env_list *env_lst)
{
	t_cmd_node *current;
	int fd_stdin_backup;
	int fd_stdout_backup;

	fd_stdin_backup = backup_fd(STDIN_FILENO);
	fd_stdout_backup = backup_fd(STDOUT_FILENO);
	if(fd_stdin_backup == -1 || fd_stdout_backup == -1)
		return 1;

	current = cmd_lst->head;
	if(current->cmd_type)//BUILTIN
		return execute_builtin(current, env_lst);
	else
		return execute_external_command(cmd_lst, env_lst);

	restore_fd(STDIN_FILENO, fd_stdin_backup);
	restore_fd(STDOUT_FILENO, fd_stdout_backup);
	return 0;
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
