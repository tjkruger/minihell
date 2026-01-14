/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjkruger <tjkruger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 13:03:14 by tjkruger          #+#    #+#             */
/*   Updated: 2026/01/14 15:15:51 by tjkruger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

void	setup_signals_child(void);
void	handle_sigint_interactive(int sig);
void	setup_signals_interactive(void);
void	setup_signals_heredoc(void);
void	heredoc_sigint(int sig);
#endif