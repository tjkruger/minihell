/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaraogl <hkaraogl@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 12:27:02 by hkaraogl          #+#    #+#             */
/*   Updated: 2026/01/14 14:56:42 by hkaraogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRONMENT_H
# define ENVIRONMENT_H

// environment.c
int			set_env_value(t_env_list *env, char *key, char *value,
				int exported);
char		*find_command_path(t_trash *trash, char *cmd);
void		add_env_node(t_env_list *env, char *key, char *value, int exported);
int			count_exported_vars(t_env_list *env);
int			fill_env_array(char **arr, t_env_list *env);

// environment_utils.c
t_env_node	*find_env_node(t_env_list *env, char *key);
char		*get_env_value(t_env_list *env, char *key);
int			set_env_value(t_env_list *env, char *key, char *value,
				int exported);
int			unset_env_value(t_env_list *env, char *key);
char		**env_list_array(t_env_list *env);

#endif