/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaraogl <hkaraogl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 17:29:21 by hkaraogl          #+#    #+#             */
/*   Updated: 2025/12/17 16:16:18 by hkaraogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int handle_input_redir(char *filename)
{
	int fd;
	if(!filename)
		return 0;
	
	fd = open(filename, O_RDONLY);
	if(fd == -1)
	{
		perror("open");
		return 0;
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return 1;
}

static int handle_output_redir(char *filename)
{
	int fd;

	if(!filename)
		return 0;
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if(fd == -1)
	{
		perror("open");
		return 0;
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return 1;
}

static int handle_append_redir(char *filename)
{
	int fd;

	if(!filename)
		return 0;
	fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if(fd == -1)
	{
		perror("open");
		return 0;
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return 1;
}
//heredoc: temp file muss ich main erstellt werden
int handle_heredoc_redir(char *filename)
{
	return (handle_input_redir(filename));
}

static int apply_redirections(t_file_node *file)
{
	if(file->redir_type == TOKEN_REDIR_IN)
		return (handle_input_redir(file->filename));
	else if(file->redir_type == TOKEN_REDIR_OUT)
		return (handle_output_redir(file->filename));
	else if(file->redir_type == TOKEN_REDIR_APPEND)
		return (handle_append_redir(file->filename));
	else if(file->redir_type == TOKEN_REDIR_HEREDOC)
		return (handle_heredoc_redir(file->filename));
	return 1;
}

int set_redirections(t_file_list *files)
{
	t_file_node *current;

	if(!files || !files->head)
		return 1;
	current = files->head;
	while(current)
	{
		if(!apply_redirections(current))
			return 0;
		current = current->next;
	}
	return 1;
}

