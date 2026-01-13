/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaraogl <hkaraogl@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 15:49:23 by hkaraogl          #+#    #+#             */
/*   Updated: 2026/01/13 15:54:22 by hkaraogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_input_redir(char *filename)
{
	int	fd;

	if (!filename)
		return (0);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		perror("open");
		return (0);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (1);
}

int	handle_output_redir(char *filename)
{
	int	fd;

	if (!filename)
		return (0);
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("open");
		return (0);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (1);
}

int	handle_append_redir(char *filename)
{
	int	fd;

	if (!filename)
		return (0);
	fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		perror("open");
		return (0);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (1);
}

int	handle_heredoc_redir(char *filename)
{
	return (handle_input_redir(filename));
}
