/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaraogl <hkaraogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 13:08:42 by hkaraogl          #+#    #+#             */
/*   Updated: 2026/01/09 13:29:13 by hkaraogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_pipes(t_ms *ms, t_pipes *data)
{
	data->pipes = NULL;
	data->pids = NULL;
	data->command_count = ms->all_commands->size;
	data->pipe_count = ms->all_commands->size - 1;
	if (data->pipe_count > 0)
	{
		data->pipes = create_pipes(&ms->trash, data->pipe_count);
		if (!data->pipes)
			return (0);
	}
	data->pids = gc_malloc(&ms->trash, ms->all_commands->size, sizeof(pid_t));
	if (!data->pids)
		return (0);
	return (1);
}

void	free_pipes(t_pipes *data)
{
	int	i;

	i = 0;
	if (!data->pipes)
		return ;
	while (i < data->pipe_count)
	{
		free(data->pipes[i]);
		i++;
	}
	free(data->pipes);
	free(data->pids);
}

int	close_all_pipes(t_pipes *data)
{
	int	i;

	i = 0;
	while (i < data->pipe_count)
	{
		close(data->pipes[i][0]);
		close(data->pipes[i][1]);
		i++;
	}
	return (0);
}

// creates pipes array
// exaample: pipes[0] = [read0, write0], pipes[1] = [read1, write1],
int	**create_pipes(t_trash *trash, int count)
{
	int	**pipes;
	int	i;

	i = 0;
	pipes = gc_malloc(trash, count, sizeof(int *));
	if (!pipes)
		return (NULL);
	while (i < count)
	{
		pipes[i] = gc_malloc(trash, 2, sizeof(int));
		if (!pipes[i])
		{
			// cleanup free(pipes)
			return (NULL);
		}
		if (pipe(pipes[i]) == -1)
		{
			perror("pipe");
			// cleanup
			return (NULL);
		}
		i++;
	}
	return (pipes);
}
