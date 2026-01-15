/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjkruger <tjkruger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 15:45:59 by tjkruger          #+#    #+#             */
/*   Updated: 2026/01/15 14:29:26 by tjkruger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern volatile sig_atomic_t	g_signal_status;

// void	print_tokens(t_token *tok)
// {
// 	int	i;

// 	i = 0;
// 	while (tok)
// 	{
// 		printf("tok[%d] type=%d value='%s' dna='%s'\n",
// 			i,
// 			tok->type,
// 			tok->value ? tok->value : "(null)",
// 			tok->dna ? tok->dna : "(null)",
// 			tok->type ? tok->type : "(null)");
// 		tok = tok->next;
// 		i++;
// 	}
// }

void	free_all_environment(t_env_list *env_lst)
{
	t_env_node	*current;
	t_env_node	*next;

	if (!env_lst)
		return ;
	current = env_lst->head;
	while (current)
	{
		next = current->next;
		free(current->key);
		free(current->value);
		free(current);
		current = next;
	}
	free(env_lst);
}

/* initialize shell runtime state (ms) */
static void	init_ms(t_ms *ms, char **env)
{
	ms->history_list = NULL;
	ms->all_commands = NULL;
	ms->token = NULL;
	ms->curr_cmd = NULL;
	ms->env_list = init_environment(env);
	rl_catch_signals = 0;
	rl_catch_sigwinch = 0;
	init_shell_level(ms);
	setup_signals_interactive();
	trash_init(&ms->trash);
}

static void	shutdown_ms(t_ms *ms)
{
	free_all_environment(ms->env_list);
	free_hist(ms->history_list);
}

/* handle the "history" builtin line */
int	handle_history_line(t_ms *ms, char *input)
{
	if (strcmp(input, "history") != 0)
		return (0);
	print_history(ms->history_list);
	return (1);
}

/* main: short dispatch loop */
int	main(int argc, char **argv, char **env)
{
	t_ms	ms;
	int		exit_status;

	(void)argc;
	(void)argv;
	exit_status = 0;
	init_ms(&ms, env);
	while (readline_iteration(&ms, &exit_status))
		;
	shutdown_ms(&ms);
	return (exit_status);
}
