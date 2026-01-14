/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_list_helper.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjkruger <tjkruger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 15:03:15 by tjkruger          #+#    #+#             */
/*   Updated: 2026/01/14 15:05:27 by tjkruger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_one_command	*create_new_command_node(t_trash *trash)
{
	t_one_command	*new_command;

	new_command = gc_malloc(trash, 1, sizeof(t_one_command));
	if (!new_command)
		return (NULL);
	new_command->cmd_type = 0;
	new_command->executable = 0;
	new_command->cmd = NULL;
	new_command->files = NULL;
	new_command->next = NULL;
	return (new_command);
}

t_all_commands	*create_new_commands_list(t_trash *trash)
{
	t_all_commands	*list;

	list = gc_malloc(trash, 1, sizeof(t_all_commands));
	if (!list)
		return (NULL);
	list->head = NULL;
	list->tail = NULL;
	list->size = 0;
	list->syntax_error = 0;
	return (list);
}

void	add_word_to_cmd(t_one_command *curr_cmd, char *value, t_trash *trash)
{
	int		i;
	int		j;
	char	**new_cmd;

	i = 0;
	j = 0;
	if (curr_cmd->cmd)
	{
		while (curr_cmd->cmd[i] != NULL)
			i++;
	}
	new_cmd = gc_malloc(trash, (i + 2), sizeof(char *));
	if (!new_cmd)
		return ;
	while (j < i)
	{
		new_cmd[j] = curr_cmd->cmd[j];
		j++;
	}
	new_cmd[i] = gc_strdup(trash, value);
	new_cmd[i + 1] = NULL;
	curr_cmd->cmd = new_cmd;
}

void	add_cmd_to_list(t_all_commands *cmd_list, t_one_command *curr_cmd)
{
	if (!cmd_list || !curr_cmd)
		return ;
	curr_cmd->next = NULL;
	if (cmd_list->head == NULL)
	{
		cmd_list->head = curr_cmd;
		cmd_list->tail = curr_cmd;
	}
	else
	{
		cmd_list->tail->next = curr_cmd;
		cmd_list->tail = curr_cmd;
	}
	cmd_list->size++;
}

int	find_executable(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '.')
		if (str[++i] == '/')
			return (1);
	return (0);
}
