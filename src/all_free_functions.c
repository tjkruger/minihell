/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_free_functions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjkruger <tjkruger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 15:35:30 by tjkruger          #+#    #+#             */
/*   Updated: 2026/01/14 15:36:56 by tjkruger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cmd_list(t_all_commands *cmds)
{
	t_one_command	*tmp;
	int				i;

	if (!cmds)
		return ;
	while (cmds && cmds->head)
	{
		tmp = cmds->head->next;
		if (cmds->head->cmd)
		{
			i = 0;
			while (cmds->head->cmd[i])
			{
				free(cmds->head->cmd[i]);
				i++;
			}
			free(cmds->head->cmd);
		}
		free_file_list(cmds->head->files);
		free(cmds->head);
		cmds->head = tmp;
	}
	free(cmds);
}

void	free_file_list(t_file_list *files)
{
	t_file_node	*tmp;

	while (files && files->head)
	{
		tmp = files->head->next;
		free(files->head->filename);
		free(files->head->delimiter);
		free(files->head);
		files->head = tmp;
	}
	free(files);
}

void	free_token_list(t_token *head)
{
	t_token	*tmp;

	if (!head)
		return ;
	while (head)
	{
		tmp = head->next;
		free(head->value);
		free(head->dna);
		free(head);
		head = tmp;
	}
}

void	free_hist(t_history *history_list)
{
	t_history	*tmp;

	while (history_list)
	{
		tmp = history_list->next;
		free(history_list->command);
		free(history_list);
		history_list = tmp;
	}
}

void	free_pretoken(t_pretoken *pt)
{
	int	i;

	i = 0;
	if (!pt)
		return ;
	if (pt->token)
	{
		while (pt->token[i])
		{
			free(pt->token[i]);
			i++;
		}
		free(pt->token);
	}
	i = 0;
	if (pt->dna)
	{
		while (pt->dna[i])
		{
			free(pt->dna[i]);
			i++;
		}
		free(pt->dna);
	}
	free(pt);
}
