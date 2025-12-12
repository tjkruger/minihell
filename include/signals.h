/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaraogl <hkaraogl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 13:03:14 by tjkruger          #+#    #+#             */
/*   Updated: 2025/12/09 15:51:59 by hkaraogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

void handle_sigint(int sig);
void handle_sigquit(int sig);
void handle_sigint_child(int sig);
void handle_sigquit_child(int sig);
void setup_signals_interactive(void);
void reset_signals_default(void);
#endif