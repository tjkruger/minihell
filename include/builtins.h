/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjkruger <tjkruger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 14:32:01 by tjkruger          #+#    #+#             */
/*   Updated: 2026/01/15 14:32:04 by tjkruger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

int		run_echo(t_one_command *cmd_node);
int		run_cd(char **args, t_env_list *env);
int		run_pwd(void);
int		run_unset(char **cmd, t_env_list *env);
int		run_exit(t_ms *ms);
int		run_env(t_env_list *env);
int		run_export(t_env_list *env, char **cmd);
void	swap_content(t_env_node *node1, t_env_node *node2);

#endif
