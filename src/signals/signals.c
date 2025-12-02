/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjkruger <tjkruger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 12:34:28 by tjkruger          #+#    #+#             */
/*   Updated: 2025/12/02 13:05:27 by tjkruger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_exit_status = 0;

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
