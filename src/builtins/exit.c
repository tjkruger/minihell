/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaraogl <hkaraogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 20:39:00 by hkaraogl          #+#    #+#             */
/*   Updated: 2026/01/08 16:47:04 by hkaraogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	cleanup_exit(t_ms *ms, int exit_code)
{
	free_hist(ms->history_list);
	free_all_environment(ms->env_list);
	gc_cleanup(&ms->trash);
	exit(exit_code);
}

static int	is_valid_nbr(char *nbr)
{
	int	i;
	int	len_counter;

	i = 0;
	len_counter = 0;
	while (nbr[i] && (nbr[i] == ' ' || nbr[i] == '\t'))
		i++;
	if (nbr[i] == '+' || nbr[i] == '-')
		i++;
	if (!nbr[i] || !ft_isdigit(nbr[i]))
		return (0);
	while (nbr[i])
	{
		if (!ft_isdigit(nbr[i]))
			break ;
		i++;
		len_counter++;
	}
	if (!nbr[i] && len_counter <= 9)
		return (1);
	else
		return (0);
}

void	print_err_msg(t_ms *ms)
{
	ft_putstr_fd("bash: exit: ", 2);
	ft_putstr_fd(ms->all_commands->head->cmd[1], 2);
	ft_putendl_fd(": numeric argument required", 2);
}

int	run_exit(t_ms *ms)
{
	int	exit_code;
	int	last_exit;

	if (isatty(STDIN_FILENO))
		ft_putendl_fd("exit", 2);
	last_exit = ms->env_list->last_exit;
	if (!ms->all_commands->head->cmd[1])
		cleanup_exit(ms, last_exit);
	if (ms->all_commands->head->cmd[2])
	{
		ft_putendl_fd("bash: exit: too many arguments", 2);
		return (1);
	}
	if (!is_valid_nbr(ms->all_commands->head->cmd[1]))
	{
		print_err_msg(ms);
		cleanup_exit(ms, 2);
	}
	exit_code = ft_atoi(ms->all_commands->head->cmd[1]);
	exit_code = exit_code % 256;
	if (exit_code < 0)
		exit_code = 256 + exit_code;
	cleanup_exit(ms, exit_code);
	return (0);
}
