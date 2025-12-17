/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaraogl <hkaraogl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 12:27:02 by hkaraogl          #+#    #+#             */
/*   Updated: 2025/12/17 15:21:44 by hkaraogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRONMENT_H
# define ENVIRONMENT_H

char		**env_list_array(t_trash *trash, t_env_list *env);
int			unset_env_value(t_env_list *env, char *key);
int			set_env_value(t_trash *trash, t_env_list *env, char *key, char *value, int exported);
t_env_node	*find_env_node(t_env_list *env, char *key);
char	*find_command_path(char *cmd);
void		add_env_node(t_trash *trash, t_env_list *env, char *key, char *value, int exported);
t_env_list	*init_environment(t_trash *trash, char **system_env);
char	*get_env_value(t_env_list *env, char *key);

#endif