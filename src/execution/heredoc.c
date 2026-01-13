/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaraogl <hkaraogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 18:18:13 by hkaraogl          #+#    #+#             */
/*   Updated: 2026/01/09 13:29:16 by hkaraogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include    "minishell.h"

static char *generate_tmpfile_name(t_trash *trash)
{
	static int counter = 0;
	char *appendix;
	char *temp;

	appendix = ft_itoa(counter);
	if(!appendix)
		return NULL;
	temp = gc_strjoin(trash, "/tmp/.minishell_heredoc_", appendix);
	free(appendix);
	counter++;
	return temp;
}

void heredoc_sigint(int sig)
{
	(void)sig;
	g_signal_status = SIGINT;       // tell shell Ctrl-C happened
	write(STDOUT_FILENO, "\nminisHell> ", 12);  // optional newline
	rl_done = 1;                     // exit readline loop
}

void setup_signals_heredoc(void)
{
	struct sigaction sa;

	sa.sa_handler = heredoc_sigint;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);

	// heredoc ignores SIGQUIT
	signal(SIGQUIT, SIG_IGN);
}

// prints a single token to fd, respecting the dna string for quotes
void printout_token(int fd, char *value)
{
	if (!value)
		return;
	write(fd, value, ft_strlen(value));
}


//this function will executed only if heredoc *file exists
//create tmp file,
//collect input,
//expand if needed
//save tmp file
static int	setup_heredoc(t_ms *ms, t_file_node *file)
{
	t_token *temp_token_heredoc;
	char *tmp_file;
	char *line;
	int fd = 0;
	tmp_file = generate_tmpfile_name(&ms->trash);
	
	fd = open(tmp_file, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if(fd == -1)
		return (perror("heredoc tmp file"), 0);

	setup_signals_heredoc(); //signal setup for heredoc
	while(1)
	{
		line = readline("heredoc:");
		if (g_signal_status == SIGINT)
		{
			free(line);
			close(fd);
			unlink(tmp_file); // delete temp file
			g_signal_status = 0;
			ms->env_list->last_exit = 130;
			return 0;         // abort heredoc
		}
		if(!line)
		{
			ft_putstr_fd("minishell: warning: here-document delimited by end-of-file (wanted `", STDERR_FILENO);
			ft_putstr_fd(file->delimiter, STDERR_FILENO);
			ft_putstr_fd("')\n", STDERR_FILENO);
			break;
		}
		
		if(ft_strcmp(line, file->delimiter) == 0)
		{
			free(line);
			break;
		}
		temp_token_heredoc = tokenize(line, ms);
		if (line[0] == '\0')
		{
			write(fd, "\n", 1);
			free(line);
			continue;
		}

		if(!file->qoutes_in_heredoc)
			handle_expansions(temp_token_heredoc, ms->env_list, &ms->trash);
		while(temp_token_heredoc)
		{
			printout_token(fd, temp_token_heredoc->value);
			if (temp_token_heredoc->next)
				write(fd, " ", 1);
			temp_token_heredoc = temp_token_heredoc->next;
		}
		write(fd, "\n", 1);
		free(line);
	}
	close(fd);
	file->filename = tmp_file;
	setup_signals_interactive();
	return 1;
}

int setup_all_heredoc(t_ms *ms)
{
	t_one_command *current;
	t_file_node *file;

	current = ms->all_commands->head;
	while(current)
	{
		if(current->files && current->files->head)
		{
			file = current->files->head;
			while(file)
			{
				if(file->redir_type == TOKEN_REDIR_HEREDOC)
				{
					if(!setup_heredoc(ms, file))
						return 0;
				}
				file = file->next;
			}
		}
		current = current->next;
	}
	return 1;
}
