/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjkruger <tjkruger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 18:18:13 by hkaraogl          #+#    #+#             */
/*   Updated: 2026/01/14 15:21:37 by tjkruger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern volatile sig_atomic_t	g_signal_status;

static int	read_heredoc_input(int fd, t_file_node *file, t_ms *ms, char *tmp)
{
	char	*line;

	while (1)
	{
		line = readline("heredoc:");
		if (g_signal_status == SIGINT)
			return (handle_heredoc_interrupt(fd, line, tmp, ms));
		if (handle_heredoc_eof(line, file->delimiter))
			break ;
		if (ft_strcmp(line, file->delimiter) == 0)
		{
			free(line);
			break ;
		}
		process_heredoc_line(fd, line, file, ms);
		free(line);
	}
	return (1);
}

static int	open_heredoc_file(char *tmp_file)
{
	int	fd;

	fd = open(tmp_file, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (fd == -1)
	{
		perror("heredoc tmp file");
		return (-1);
	}
	return (fd);
}

static int	setup_heredoc(t_ms *ms, t_file_node *file)
{
	char	*tmp_file;
	int		fd;
	int		result;

	tmp_file = generate_tmpfile_name(&ms->trash);
	fd = open_heredoc_file(tmp_file);
	if (fd == -1)
		return (0);
	setup_signals_heredoc();
	result = read_heredoc_input(fd, file, ms, tmp_file);
	close(fd);
	if (result)
		file->filename = tmp_file;
	setup_signals_interactive();
	return (result);
}

static int	process_command_heredocs(t_ms *ms, t_one_command *cmd)
{
	t_file_node	*file;

	if (!cmd->files || !cmd->files->head)
		return (1);
	file = cmd->files->head;
	while (file)
	{
		if (file->redir_type == TOKEN_REDIR_HEREDOC)
		{
			if (!setup_heredoc(ms, file))
				return (0);
		}
		file = file->next;
	}
	return (1);
}

int	setup_all_heredoc(t_ms *ms)
{
	t_one_command	*current;

	current = ms->all_commands->head;
	while (current)
	{
		if (!process_command_heredocs(ms, current))
			return (0);
		current = current->next;
	}
	return (1);
}
