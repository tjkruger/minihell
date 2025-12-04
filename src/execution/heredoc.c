/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaraogl <hkaraogl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 18:18:13 by hkaraogl          #+#    #+#             */
/*   Updated: 2025/12/04 14:36:00 by hkaraogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include    "minishell.h"

//must be freed by user
static char *generate_tmpfile_name(void)
{
	static int counter = 0;
	char *appendix;
	char *temp;

	appendix = ft_itoa(counter);
	if(!appendix)
		return NULL;
	temp = ft_strjoin("/tmp/.minishell_heredoc_", appendix);
	free(appendix);
	counter++;
	return temp;
}

void	cleanup_heredoc_file(char *filename)
{
	if(filename)
	{
		if(unlink(filename) == -1)
		{
			perror("unlinked failed");
			free(filename);
			return;
		}
		free(filename);
	}
}
//iterate through cmd_lst and iterate through each nodes file lst
//unlink heredoc temp file
//this function frees the filename of the filenode and unlink (delete)  in the filelist. So be careful freeing it again somewhere else!!!!
void	cleanup_all_heredoc_files(t_all_commands *cmd_lst)
{
	t_one_command *current;
	t_file_node *file;

	if(!cmd_lst || !cmd_lst->head)
		return;
	current = cmd_lst->head;
	while(current)
	{
		if(current->files)
		{
			file = current->files->head;
			while(file)
			{
				if(file->redir_type == TOKEN_REDIR_HEREDOC && file->filename)
				{
					unlink(file->filename);
					free(file->filename);
					file->filename = NULL;
				}
				file = file->next;
			}
		}
		current = current->next;
	}
}



//this function will executed only if heredoc *file exists
//create tmp file,
//collect input,
//expand if needed
//save tmp file
int	setup_heredoc(t_file_node *file, t_env_list *env_lst)
{
	char *tmp_file;
	char *line;
	int fd = 0;
	tmp_file = generate_tmpfile_name();
	
	fd = open(tmp_file, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if(fd == -1)
		return (perror("heredoc tmp file"), 0);

	while(1)
	{
		line = readline("heredoc:");
		if(!line)
			break;
		
		if(ft_strcmp(line, file->filename) == 0)
		{
			free(line);
			break;
		}
		//expand if needed
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	close(fd);
	file->filename = tmp_file;
	return 1;
}

int setup_all_heredoc(t_all_commands *cmd_lst, t_env_list *env_lst)
{
	t_one_command *current;
	t_file_node *file;

	current = cmd_lst->head;
	while(current)
	{
		if(current->files && current->files->head)
		{
			file = current->files->head;
			while(file)
			{
				if(file->redir_type == TOKEN_REDIR_HEREDOC)
				{
					if(!setup_heredoc(file, env_lst))
						return 0;
				}
				file = file->next;
			}
		}
		current = current->next;
	}
	return 1;
}