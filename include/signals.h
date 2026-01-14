/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaraogl <hkaraogl@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 13:03:14 by tjkruger          #+#    #+#             */
/*   Updated: 2026/01/14 14:56:55 by hkaraogl         ###   ########.fr       */
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