/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjkruger <tjkruger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 13:45:15 by hkaraogl          #+#    #+#             */
/*   Updated: 2026/01/15 14:29:32 by tjkruger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

int		count_array_string(char **arr);
void	free_str_arr(char **arr);
int		strncmp_strlen(char *s1, char *s2);
int		is_valid_identifier(char *str);
char	*has_equal(char *str);
int		ft_strcmp(char *s1, char *s2);
void	ft_perror(char *msg);
void	print_cmd_error(char *cmd, char *msg);
int		error_exit_perror(char *context, int code);
int		error_exit(char *cmd, char *msg, int code);
void	sort_env(t_env_list *env);
void	print_export_error(char *arg);
int		is_absolut_path(char *cmd);
char	*ft_strncpy(char *dest, const char *src, size_t n);
int		prepare_commands(t_ms *ms, char *input);
int		execute_and_cleanup(t_ms *ms);
void	process_line(t_ms *ms, char *input, int *exit_status);
int		readline_iteration(t_ms *ms, int *exit_status);
int		handle_history_line(t_ms *ms, char *input);

#endif