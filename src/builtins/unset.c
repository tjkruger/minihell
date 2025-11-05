/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaraogl <hkaraogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 15:09:29 by hkaraogl          #+#    #+#             */
/*   Updated: 2025/11/05 15:47:08 by hkaraogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//cmd = {unset, VAR1, VAR2, NULL}
// unset                    # Exit 0, macht nichts
// unset VAR                # Exit 0, löscht VAR falls vorhanden
// unset DOES_NOT_EXIST     # Exit 0, macht nichts
// unset 12VAR              # Exit 0, ignoriert ungültigen Namen
// unset @#$%               # Exit 0, ignoriert ungültigen Namen
// unset VAR1 VAR2 VAR3     # Exit 0, löscht alle gültigen
// unset VAR1 123 VAR2      # Exit 0, löscht VAR1 und VAR2, ignoriert 123
// unset ""                 # Exit 0, macht nichts
int run_unset(char **cmd, t_env_list *env)
{
	int i;

	i = 1;
	while(cmd[i])
	{
		unset_env_value(env, cmd[i]);
		i++;
	}
	return 0;
}