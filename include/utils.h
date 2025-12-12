/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaraogl <hkaraogl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 13:45:15 by hkaraogl          #+#    #+#             */
/*   Updated: 2025/12/11 18:51:28 by hkaraogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
#define UTILS_H

int count_array_string(char **arr);
void	free_str_arr(char **arr);
int	strncmp_strlen(char *s1, char *s2);
int	is_valid_identifier(char *str);
char *has_equal(char *str);
int ft_strcmp(char *s1, char *s2);
void	ft_perror(char *msg);
void print_cmd_error(char *cmd, char *msg);
int	error_exit_perror(char *context, int code);
int	error_exit(char *cmd, char*msg, int code);
void print_all_cmd(t_all_commands *cmd_lst);
int validate_command(t_one_command *cmd);

#endif