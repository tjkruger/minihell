/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaraogl <hkaraogl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 14:55:36 by hkaraogl          #+#    #+#             */
/*   Updated: 2026/01/07 13:24:48 by hkaraogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

int	execute_commands(t_ms *ms);
int get_exit_status(int status);
int process_builtin(t_one_command *node, t_ms *ms);
int	execute_external_command(t_ms *ms, t_one_command *cmd);

//redirection
int set_redirections(t_file_list *files);
int handle_heredoc_redir(char *filename);

//child.c
int wait_all_children(t_pipes *data);
void setup_child_pipes(t_pipes *data, int index);
void execute_child(t_ms *ms, t_one_command *cmd, t_pipes *data, int index);


//pipes.c
int **create_pipes(t_trash *trash, int count);
void	free_pipes(t_pipes *data);
int	close_all_pipes(t_pipes *data);

//fd.c
void backup_fds(int *fd_backups);
void restore_fds(int *fd_backups);
void restore_fd(int fd, int backup);
int backup_fd(int fd);
void init_fd_backups(int *fd_backups);

//heredoc.c
int setup_all_heredoc(t_ms *ms);
// void	cleanup_all_heredoc_files(t_all_commands *cmd_lst);

void print_array(char **arr);

#endif