/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaraogl <hkaraogl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 13:12:09 by hkaraogl          #+#    #+#             */
/*   Updated: 2025/12/02 13:13:44 by hkaraogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void init_fd_backups(int *fd_backups)
{
	fd_backups[0] = -1;
	fd_backups[1] = -1;
}

int backup_fd(int fd)
{
	int backup;
	backup = dup(fd);
	if(backup == -1)
	{
		perror("dup");
		return -1;
	}
	return backup;
}

void restore_fd(int fd, int backup)
{
	if(backup == -1)
		return;
	if(dup2(backup, fd) == -1)
		ft_perror("dup2");
	close(backup);
}

void restore_fds(int *fd_backups)
{
	restore_fd(STDIN_FILENO, fd_backups[0]);
	restore_fd(STDOUT_FILENO, fd_backups[1]);
}



void backup_fds(int *fd_backups)
{
	fd_backups[0] = backup_fd(STDIN_FILENO);
	fd_backups[1] = backup_fd(STDOUT_FILENO);
}