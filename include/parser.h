/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaraogl <hkaraogl@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 13:03:26 by tjkruger          #+#    #+#             */
/*   Updated: 2026/01/14 16:07:56 by hkaraogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "structs.h"

int				find_cmd_type(char **cmd);
int				find_executable(char *str);
void			add_word_to_cmd(t_one_command *curr_cmd, char *value,
					t_trash *trash);
void			add_cmd_to_list(t_all_commands *cmd_list,
					t_one_command *curr_cmd);
void			add_file_to_cmd(t_ms *ms, char *value, int redir_type,
					char *dna);
t_file_list		*init_file_list(t_ms *ms);
t_file_node		*create_file_node(t_ms *ms, char *value, char *dna,
					t_token_type redir_type);
t_all_commands	*create_new_commands_list(t_trash *trash);
t_all_commands	*build_commands(t_ms *ms);
t_one_command	*create_new_command_node(t_trash *trash);

#endif
