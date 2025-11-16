/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: r2d2 <r2d2@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 15:32:10 by tjkruger          #+#    #+#             */
/*   Updated: 2025/11/13 17:33:09 by r2d2             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef HISTORY_H
# define HISTORY_H

#include "structs.h"

int is_empty_or_whitespace(const char *s);
t_history *add_to_hist_list(t_history **list, char *command_to_list);
void print_history(t_history *list);
void free_hist(t_history *history_list);

#endif

