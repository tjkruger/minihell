/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_initialisation-handeling.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjkruger <tjkruger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 15:01:00 by tjkruger          #+#    #+#             */
/*   Updated: 2026/01/14 17:17:45 by tjkruger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_file_list	*init_file_list(t_ms *ms)
{
	t_file_list	*list;

	list = gc_malloc(&ms->trash, 1, sizeof(t_file_list));
	if (!list)
		return (NULL);
	list->head = NULL;
	list->tail = NULL;
	list->size = 0;
	return (list);
}

t_file_node	*create_file_node(t_ms *ms, char *value, char *dna,
		t_token_type redir_type)
{
	t_file_node	*node;

	node = gc_malloc(&ms->trash, 1, sizeof(t_file_node));
	if (!node)
		return (NULL);
	node->qoutes_in_heredoc = 0;
	if (redir_type == TOKEN_REDIR_HEREDOC)
	{
		node->filename = NULL;
		node->delimiter = gc_strdup(&ms->trash, value);
		if (dna && (ft_strchr(dna, 'D') || ft_strchr(dna, 'S')))
			node->qoutes_in_heredoc = 1;
	}
	else
	{
		node->filename = gc_strdup(&ms->trash, value);
		node->delimiter = NULL;
	}
	node->redir_type = redir_type;
	node->next = NULL;
	return (node);
}

static void	ensure_file_list(t_ms *ms)
{
	if (!ms || !ms->curr_cmd)
		return ;
	if (!ms->curr_cmd->files)
		ms->curr_cmd->files = init_file_list(ms);
}

static void	append_file_node(t_ms *ms, t_file_node *node)
{
	t_file_list	*files;

	if (!ms || !ms->curr_cmd || !node)
		return ;
	files = ms->curr_cmd->files;
	if (!files->head)
	{
		files->head = node;
		files->tail = node;
	}
	else
	{
		files->tail->next = node;
		files->tail = node;
	}
	files->size++;
}

void	add_file_to_cmd(t_ms *ms, char *value, int redir_type, char *dna)
{
	t_file_node	*new_file;

	if (!ms || !value || !ms->curr_cmd)
		return ;
	ensure_file_list(ms);
	new_file = create_file_node(ms, value, dna, redir_type);
	if (!new_file)
		return ;
	append_file_node(ms, new_file);
}
