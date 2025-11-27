/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaraogl <hkaraogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 13:45:15 by hkaraogl          #+#    #+#             */
/*   Updated: 2025/11/25 14:18:13 by hkaraogl         ###   ########.fr       */
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

#endif