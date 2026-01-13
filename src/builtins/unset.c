/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaraogl <hkaraogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 15:09:29 by hkaraogl          #+#    #+#             */
/*   Updated: 2026/01/08 16:46:21 by hkaraogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	run_unset(char **cmd, t_env_list *env)
{
	int	i;

	i = 1;
	while (cmd[i])
	{
		unset_env_value(env, cmd[i]);
		i++;
	}
	return (0);
}
