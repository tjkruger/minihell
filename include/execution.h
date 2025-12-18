/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaraogl <hkaraogl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 14:55:36 by hkaraogl          #+#    #+#             */
/*   Updated: 2025/12/18 13:41:11 by hkaraogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

int	execute_commands(t_trash *trash, t_all_commands *cmd_lst, t_env_list *env_lst);
int get_exit_status(int status);
int process_builtin(t_one_command *node, t_env_list *env_lst);
int	execute_external_command(t_trash *trash, t_one_command *cmd, t_env_list *env_lst);

//redirection
int set_redirections(t_file_list *files);
int handle_heredoc_redir(char *filename);

//child.c
int wait_all_children(t_pipes *data);
void setup_child_pipes(t_pipes *data, int index);
void execute_child(t_trash *trash, t_one_command *cmd, t_pipes *data, t_env_list *env, int index);


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
int setup_all_heredoc(t_trash *trash, t_all_commands *cmd_lst, t_env_list *env_lst);
// void	cleanup_all_heredoc_files(t_all_commands *cmd_lst);

#endif