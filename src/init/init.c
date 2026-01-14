/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaraogl <hkaraogl@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 12:54:13 by hkaraogl          #+#    #+#             */
/*   Updated: 2026/01/14 14:57:30 by hkaraogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_shell_level(t_ms *ms)
{
	char	*shlvl_str;
	char	*new_shlvl_str;
	int		shlvl;

	shlvl_str = get_env_value(ms->env_list, "SHLVL");
	if (!shlvl_str)
		shlvl = 1;
	else
	{
		shlvl = ft_atoi(shlvl_str);
		shlvl++;
	}
	if (shlvl <= 0)
		shlvl = 1;
	new_shlvl_str = ft_itoa(shlvl);
	if (shlvl == 3)
		setup_signals_interactive();
	else
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
	set_env_value(ms->env_list, "SHLVL", new_shlvl_str, 1);
	free(new_shlvl_str);
}
