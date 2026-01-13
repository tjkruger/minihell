/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaraogl <hkaraogl@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 15:57:40 by hkaraogl          #+#    #+#             */
/*   Updated: 2026/01/13 16:04:39 by hkaraogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	fork_single_child(t_ms *ms, t_one_command *cmd, t_pipes *data,
		int i)
{
	data->pids[i] = fork();
	if (data->pids[i] == -1)
	{
		ft_perror("fork");
		return (0);
	}
	if (data->pids[i] == 0)
	{
		setup_signals_child();
		execute_child(ms, cmd, data, i);
	}
	return (1);
}

static int	fork_all_children(t_ms *ms, t_pipes *data)
{
	t_one_command	*current;
	int				i;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	i = 0;
	current = ms->all_commands->head;
	while (current)
	{
		if (!fork_single_child(ms, current, data, i))
			return (0);
		current = current->next;
		i++;
	}
	return (1);
}

static void	cleanup_pipes_and_signals(t_pipes *data)
{
	close_all_pipes(data);
	setup_signals_interactive();
}

int	execute_with_pipes(t_ms *ms)
{
	t_pipes			data;
	t_one_command	*current;
	int				status;

	if (!init_pipes(ms, &data))
		return (ft_perror("failed to initialize pipes"), 1);
	if (!fork_all_children(ms, &data))
	{
		cleanup_pipes_and_signals(&data);
		return (1);
	}
	close_all_pipes(&data);
	status = wait_all_children(&data);
	setup_signals_interactive();
	return (status);
}
