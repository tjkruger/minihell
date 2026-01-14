/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaraogl <hkaraogl@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 14:55:36 by hkaraogl          #+#    #+#             */
/*   Updated: 2026/01/14 14:56:42 by hkaraogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

// execution.c
int		execute_commands(t_ms *ms);
int		process_builtin(t_one_command *node, t_ms *ms);
int		execute_external_command(t_ms *ms, t_one_command *cmd);

// fork.c
int		execute_with_pipes(t_ms *ms);

// redirection
int		set_redirections(t_file_list *files);

// handle_redir.c
int		handle_input_redir(char *filename);
int		handle_output_redir(char *filename);
int		handle_append_redir(char *filename);
int		handle_heredoc_redir(char *filename);

// child.c
int		wait_all_children(t_pipes *data);
void	setup_child_pipes(t_pipes *data, int index);
void	execute_child(t_ms *ms, t_one_command *cmd, t_pipes *data, int index);

// pipes.c
int		**create_pipes(t_trash *trash, int count);
void	free_pipes(t_pipes *data);
int		close_all_pipes(t_pipes *data);
int		init_pipes(t_ms *ms, t_pipes *data);

// fd.c
void	backup_fds(int *fd_backups);
void	restore_fds(int *fd_backups);
void	restore_fd(int fd, int backup);
int		backup_fd(int fd);
void	init_fd_backups(int *fd_backups);

// heredoc.c
int		setup_all_heredoc(t_ms *ms);

// heredoc_utils.c
void	printout_token(int fd, char *value);
int		process_heredoc_line(int fd, char *line, t_file_node *file, t_ms *ms);
int		handle_heredoc_interrupt(int fd, char *line, char *tmp_file, t_ms *ms);
int		handle_heredoc_eof(char *line, char *delimiter);
char	*generate_tmpfile_name(t_trash *trash);

void	print_array(char **arr);

#endif