/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaraogl <hkaraogl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 20:39:00 by hkaraogl          #+#    #+#             */
/*   Updated: 2026/01/05 17:00:30 by hkaraogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//return True (1) when nbr is digit only with pre whitespaces + sign && not longer than 9 for overflowprotection
static int is_valid_nbr(char *nbr)
{
	int i = 0;
	int len_counter = 0;

	while(nbr[i] && (nbr[i] == ' ' || nbr[i] == '\t'))
		i++;
	if(nbr[i] == '+' || nbr[i] == '-')
		i++;
	if(!nbr[i] || !ft_isdigit(nbr[i]))
		return 0;
	while(nbr[i])
	{
		if(!ft_isdigit(nbr[i]))
			break;
		i++;
		len_counter++;
	}
	if(!nbr[i] && len_counter <= 9)
		return 1;
	else
		return 0;
}
// ✅ Exit wird IMMER ausgeführt außer bei zu vielen Argumenten
// ✅ Modulo 256 für alle Exit-Codes
// ✅ "exit" ausgeben bevor die Shell beendet wird
// ✅ Negative Zahlen werden zu positiven (255, 254, ...)
// ✅ Whitespace am Anfang/Ende ignorieren
// ✅ Overflow als ungültig behandeln
// ✅ Zu viele Argumente = Shell läuft weiter mit Return 1
//**cmd = {exit, 1, 2, NULL} */
int run_exit(t_ms *ms)
{
	int exit_code;
	int last_exit;

	ft_putendl_fd("exit", 1);
	last_exit = ms->env_list->last_exit;
	if(!ms->all_commands->head->cmd[1])
	{
		free_hist(ms->history_list);
		free_all_environment(ms->env_list);
		gc_cleanup(&ms->trash);
		exit(last_exit);
	}


	if(ms->all_commands->head->cmd[2])
	{
		// exit
		// bash: exit: too many arguments
		ft_putendl_fd("bash: exit: too many arguments", 1);
		return 1;
	}
	if(!is_valid_nbr(ms->all_commands->head->cmd[1]))
	{
		// exit
		// bash: exit: a2: numeric argument required
		ft_putstr_fd("bash: exit: ", 1);
		ft_putstr_fd(ms->all_commands->head->cmd[1], 1);
		ft_putendl_fd(" numeric argument required", 1);
		free_hist(ms->history_list);
		free_all_environment(ms->env_list);
		gc_cleanup(&ms->trash);
		exit(2);
	}
	exit_code = ft_atoi(ms->all_commands->head->cmd[1]);
	exit_code = exit_code % 256;
	if(exit_code < 0)
	{
		exit_code = 256 + exit_code;
	}
	free_hist(ms->history_list);
	free_all_environment(ms->env_list);
	gc_cleanup(&ms->trash);
	exit(exit_code);
	return 0;
}
