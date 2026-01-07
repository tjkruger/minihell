/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaraogl <hkaraogl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 13:08:42 by hkaraogl          #+#    #+#             */
/*   Updated: 2026/01/07 15:14:49 by hkaraogl         ###   ########.fr       */
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
int **create_pipes(t_trash *trash, int count)
{
	int **pipes;
	int i = 0;
	pipes = gc_malloc(trash, count, sizeof(int *));
	if(!pipes)
		return NULL;
	while(i < count)
	{
		pipes[i] = gc_malloc(trash, 2,  sizeof(int));
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


