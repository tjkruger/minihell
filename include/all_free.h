/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_free.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjkruger <tjkruger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 14:30:24 by tjkruger          #+#    #+#             */
/*   Updated: 2026/01/15 14:30:28 by tjkruger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALL_FREE_H
# define ALL_FREE_H

# include "structs.h"

void	free_cmd_list(t_all_commands *cmds);
void	free_file_list(t_file_list *files);
void	free_token_list(t_token *head);
void	free_hist(t_history *history_list);
void	free_pretoken(t_pretoken *pt);
void	free_all_environment(t_env_list *env_lst);

#endif