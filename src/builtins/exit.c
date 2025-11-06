/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaraogl <hkaraogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 20:39:00 by hkaraogl          #+#    #+#             */
/*   Updated: 2025/11/06 15:20:24 by hkaraogl         ###   ########.fr       */
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
int run_exit(char **cmd, int last_exit_code)
{
	int i = 0;
	int exit_code;

	ft_putendl_fd("exit", 1);
	if(!cmd[1])
	{
		//cleanup_exit(last_exit_code);
		exit(last_exit_code);
	}


	if(cmd[2])
	{
		// exit
		// bash: exit: too many arguments
		ft_putendl_fd("bash: exit: too many arguments", 1);
		return 1;
	}
	if(!is_valid_nbr(cmd[1]))
	{
		// exit
		// bash: exit: a2: numeric argument required
		ft_putstr_fd("bash: exit: ", 1);
		ft_putstr_fd(cmd[1], 1);
		ft_putendl_fd(" numeric argument required", 1);
		//cleanup_exit(2);
		exit(2);
	}
	exit_code = ft_atoi(cmd[1]);
	exit_code = exit_code % 256;
	if(exit_code < 0)
	{
		exit_code = 256 + exit_code;
	}
	//cleanup_exit(exit_code);
	exit(exit_code);
	return 0;
}
