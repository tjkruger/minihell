/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaraogl <hkaraogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 16:21:46 by hkaraogl          #+#    #+#             */
/*   Updated: 2026/01/07 18:19:03 by hkaraogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	run_env(t_env_list *env)
{
	t_env_node	*current;

	current = env->head;
	while (current)
	{
		if (current->exported)
			printf("%s=%s\n", current->key, current->value);
		current = current->next;
	}
	return (0);
}
