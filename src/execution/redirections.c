/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaraogl <hkaraogl@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 17:29:21 by hkaraogl          #+#    #+#             */
/*   Updated: 2026/01/13 15:54:09 by hkaraogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	apply_redirections(t_file_node *file)
{
	if (file->redir_type == TOKEN_REDIR_IN)
		return (handle_input_redir(file->filename));
	else if (file->redir_type == TOKEN_REDIR_OUT)
		return (handle_output_redir(file->filename));
	else if (file->redir_type == TOKEN_REDIR_APPEND)
		return (handle_append_redir(file->filename));
	else if (file->redir_type == TOKEN_REDIR_HEREDOC)
		return (handle_heredoc_redir(file->filename));
	return (1);
}

int	set_redirections(t_file_list *files)
{
	t_file_node	*current;

	if (!files || !files->head)
		return (1);
	current = files->head;
	while (current)
	{
		if (!apply_redirections(current))
			return (0);
		current = current->next;
	}
	return (1);
}
