/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaraogl <hkaraogl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 12:34:28 by tjkruger          #+#    #+#             */
/*   Updated: 2025/12/11 18:04:27 by hkaraogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t g_signal_status = 0;

// Grundlegende Signale
// SIGINT (Ctrl+C)

// Wird gesendet, wenn der User Ctrl+C drückt
// Sollte die aktuelle Zeile abbrechen und eine neue Prompt anzeigen
// Im interaktiven Modus: neue Zeile, neue Prompt
// Während ein Command läuft: den Command beenden

// SIGQUIT (Ctrl+\)

// Wird normalerweise gesendet bei Ctrl+\
// In der Shell selbst (interaktiv): sollte ignoriert werden
// Nur wenn ein Programm läuft: sollte das Programm beendet werden können

//interrupt and write newline 
void handle_sigint(int sig)
{
	(void)sig;
	g_signal_status = 130;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

//do nothing
void handle_sigquit(int sig)
{
	(void)sig;
}

void handle_sigint_child(int sig)
{
	(void)sig;
	g_signal_status = 130;
}

void handle_sigquit_child(int sig)
{
	(void)sig;
	g_signal_status = 131;
	write(STDOUT_FILENO, "Quit (core dumped)\n", 19);
}

void setup_signals_interactive(void)
{
	struct sigaction sa_input;
	struct sigaction sa_quit;

	sa_input.sa_handler = handle_sigint;
	sigemptyset(&sa_input.sa_mask);
	sa_input.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa_input, NULL);

	sa_quit.sa_handler = SIG_IGN;
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_flags = 0;
	sigaction(SIGQUIT, &sa_quit, NULL);
}

void setup_signals_child(void)
{
	struct sigaction sa_int;
	struct sigaction sa_quit;

	sa_int.sa_handler = handle_sigint_child;
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = 0;
	sigaction(SIGINT, &sa_int, NULL);

	sa_quit.sa_handler = handle_sigquit_child;
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_flags = 0;
	sigaction(SIGQUIT, &sa_quit, NULL);
}

void reset_signals_default(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

/* ************************************************************************** */
/*  HANDLERS                                                                  */
/* ************************************************************************** */

// void    parent_sigint(int sig)
// {
//     (void)sig;
//     // TODO: readline behavior: clear line, redisplay prompt
// }

// void    parent_sigquit(int sig)
// {
//     (void)sig;
//     // TODO: parent ignores SIGQUIT
// }

// void    heredoc_sigint(int sig)
// {
//     (void)sig;
//     // TODO: heredoc: exit child cleanly
// }

// void    child_default_handler(int sig)
// {
//     (void)sig;
//     // Probably unused (children use SIG_DFL)
// }

// /* ************************************************************************** */
// /*  MODE SETUP FUNCTIONS                                                      */
// /* ************************************************************************** */

// void    set_signals_parent(void)
// {
//     struct sigaction sa_int;
//     struct sigaction sa_quit;

//     sa_int.sa_handler = parent_sigint;
//     sa_int.sa_flags = SA_RESTART;
//     sigemptyset(&sa_int.sa_mask);
//     sigaction(SIGINT, &sa_int, NULL);

//     sa_quit.sa_handler = parent_sigquit;
//     sa_quit.sa_flags = SA_RESTART;
//     sigemptyset(&sa_quit.sa_mask);
//     sigaction(SIGQUIT, &sa_quit, NULL);
// }

// void    set_signals_child(void)
// {
//     // Children should always have default signal handling:
//     signal(SIGINT, SIG_DFL);
//     signal(SIGQUIT, SIG_DFL);
// }

// void    set_signals_heredoc(void)
// {
//     struct sigaction sa;

//     sa.sa_handler = heredoc_sigint;
//     sa.sa_flags = SA_RESTART;
//     sigemptyset(&sa.sa_mask);

//     sigaction(SIGINT, &sa, NULL);

//     // Heredoc ignores SIGQUIT
//     signal(SIGQUIT, SIG_IGN);
// }

// /* ************************************************************************** */
// /*  DEBUG / OPTIONAL                                                          */
// /* ************************************************************************** */

// void    debug_print_signal(int sig)
// {
//     (void)sig;
//     // optional helper if you ever want to print caught signals
// }
