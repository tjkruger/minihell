/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjkruger <tjkruger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 16:18:01 by hkaraogl          #+#    #+#             */
/*   Updated: 2026/01/14 15:22:12 by tjkruger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern volatile sig_atomic_t	g_signal_status;

char	*generate_tmpfile_name(t_trash *trash)
{
	static int	counter = 0;
	char		*appendix;
	char		*temp;

	appendix = ft_itoa(counter);
	if (!appendix)
		return (NULL);
	temp = gc_strjoin(trash, "/tmp/.minishell_heredoc_", appendix);
	free(appendix);
	counter++;
	return (temp);
}

void	printout_token(int fd, char *value)
{
	if (!value)
		return ;
	write(fd, value, ft_strlen(value));
}

int	process_heredoc_line(int fd, char *line, t_file_node *file, t_ms *ms)
{
	t_token	*tokens;

	if (line[0] == '\0')
	{
		write(fd, "\n", 1);
		return (1);
	}
	tokens = tokenize(line, ms);
	if (!file->qoutes_in_heredoc)
		handle_expansions(tokens, ms->env_list, &ms->trash);
	while (tokens)
	{
		printout_token(fd, tokens->value);
		if (tokens->next)
			write(fd, " ", 1);
		tokens = tokens->next;
	}
	write(fd, "\n", 1);
	return (1);
}

int	handle_heredoc_interrupt(int fd, char *line, char *tmp_file, t_ms *ms)
{
	free(line);
	close(fd);
	unlink(tmp_file);
	g_signal_status = 0;
	ms->env_list->last_exit = 130;
	return (0);
}

int	handle_heredoc_eof(char *line, char *delimiter)
{
	if (!line)
	{
		ft_putstr_fd("minishell: warning: here-document delimited by "
			"end-of-file (wanted `",
			STDERR_FILENO);
		ft_putstr_fd(delimiter, STDERR_FILENO);
		ft_putstr_fd("')\n", STDERR_FILENO);
		return (1);
	}
	return (0);
}
