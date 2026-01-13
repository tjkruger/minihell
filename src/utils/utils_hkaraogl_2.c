/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_hkaraogl_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaraogl <hkaraogl@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 18:00:30 by hkaraogl          #+#    #+#             */
/*   Updated: 2026/01/13 18:01:34 by hkaraogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include    "minishell.h"

void	print_export_error(char *arg)
{
	ft_putstr_fd("bash: export: `", 2);
	ft_putstr_fd(arg, 2);
	ft_putendl_fd("': not a valid identifier", 2);
}

void	sort_env(t_env_list *env)
{
	t_env_node	*current;
	t_env_node	*compare;
	char		*tmp;

	current = env->head;
	while (current)
	{
		compare = current->next;
		while (compare)
		{
			if (ft_strcmp(current->key, compare->key) > 0)
				swap_content(current, compare);
			compare = compare->next;
		}
		current = current->next;
	}
}

int	error_exit(char *cmd, char*msg, int code)
{
	print_cmd_error(cmd, msg);
	return code;
}

void print_cmd_error(char *cmd, char *msg)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(msg, 2);
}

void	ft_perror(char *msg)
{
	ft_putstr_fd("minishell: ", 2);
	perror(msg);
}