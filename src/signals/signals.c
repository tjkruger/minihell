/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjkruger <tjkruger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 12:34:28 by tjkruger          #+#    #+#             */
/*   Updated: 2026/01/14 15:23:40 by tjkruger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_signal_status = 0;

// Grundlegende Signale
// SIGINT (Ctrl+C)

// Wird gesendet, wenn der User Ctrl+C drückt
// Sollte die aktuelle Zeile abbrechen und eine neue Prompt anzeigen
// Im interaktiven Modus: neue Zeile, neue Prompt
// Während ein Command läuft: den Command beenden

// SIGQUIT (Ctrl+\)

// Wird normalerweise gesendet bei Ctrl+\\ 
// In der Shell selbst (interaktiv): sollte ignoriert werden
// Nur wenn ein Programm läuft: sollte das Programm beendet werden können

// interrupt and write newline

void	heredoc_sigint(int sig)
{
	(void)sig;
	g_signal_status = SIGINT;
	write(STDOUT_FILENO, "\nminisHell> ", 12);
	rl_done = 1;
}

void	setup_signals_heredoc(void)
{
	struct sigaction	sa;

	sa.sa_handler = heredoc_sigint;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}

void	handle_sigint_interactive(int sig)
{
	(void)sig;
	g_signal_status = SIGINT;
	rl_on_new_line();
	rl_replace_line("", 0);
	write(STDOUT_FILENO, "^C\n", 3);
	rl_redisplay();
	rl_done = 1;
}

void	setup_signals_interactive(void)
{
	struct sigaction	sa;

	sa.sa_handler = handle_sigint_interactive;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}

void	setup_signals_child(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
