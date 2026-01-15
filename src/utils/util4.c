/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjkruger <tjkruger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 14:24:49 by tjkruger          #+#    #+#             */
/*   Updated: 2026/01/15 14:28:01 by tjkruger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern volatile sig_atomic_t	g_signal_status;

int	prepare_commands(t_ms *ms, char *input)
{
	ms->token = tokenize(input, ms);
	if (!ms->token)
	{
		ms->all_commands = NULL;
		return (0);
	}
	handle_expansions(ms->token, ms->env_list, &ms->trash);
	ms->all_commands = build_commands(ms);
	if (!ms->all_commands)
		return (0);
	if (!setup_all_heredoc(ms))
	{
		ms->env_list->last_exit = 130;
		gc_cleanup(&ms->trash);
		ms->all_commands = NULL;
		return (0);
	}
	return (1);
}

/* execute built commands and cleanup per-line GC */
int	execute_and_cleanup(t_ms *ms)
{
	int	status;

	status = execute_commands(ms);
	ms->env_list->last_exit = status;
	gc_cleanup(&ms->trash);
	return (status);
}

/* process a non-empty input line (history, tokenize, exec flow) */
void	process_line(t_ms *ms, char *input, int *exit_status)
{
	if (handle_history_line(ms, input))
		return ;
	add_to_hist_list(&ms->history_list, input);
	add_history(input);
	if (!prepare_commands(ms, input))
		return ;
	*exit_status = execute_and_cleanup(ms);
}

/* single iteration of the read/handle loop; returns 0 to break main loop */
int	readline_iteration(t_ms *ms, int *exit_status)
{
	char	*input;

	input = readline("minisHell> ");
	if (g_signal_status == SIGINT)
	{
		*exit_status = 130;
		if (ms->env_list)
			ms->env_list->last_exit = 130;
		g_signal_status = 0;
		if (input)
			free(input);
		return (1);
	}
	if (!input)
	{
		write(STDOUT_FILENO, "exit\n", 5);
		return (0);
	}
	if (!is_empty_or_whitespace(input))
		process_line(ms, input, exit_status);
	free(input);
	ms->all_commands = NULL;
	ms->token = NULL;
	return (1);
}
