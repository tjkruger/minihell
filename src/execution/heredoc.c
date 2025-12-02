/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaraogl <hkaraogl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 18:18:13 by hkaraogl          #+#    #+#             */
/*   Updated: 2025/12/02 18:51:08 by hkaraogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include    "minishell.h"

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
//this function frees the filename of the filenode in the filelist. So be careful freeing it again somewhere else!!!!
void	cleanup_all_heredoc_files(t_all_commands *cmd_lst)
{
	t_one_command *current;
	t_file_node *file;

	if(!cmd_lst && !cmd_lst->head)
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
