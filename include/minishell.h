/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaraogl <hkaraogl@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 15:32:03 by tjkruger          #+#    #+#             */
/*   Updated: 2026/01/14 14:57:05 by hkaraogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <ctype.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

// header files
# include "all_free.h"
# include "builtins.h"
# include "environment.h"
# include "execution.h"
# include "history.h"
# include "init.h"
# include "lexer.h"
# include "libft.h"
# include "parser.h"
# include "signals.h"
# include "structs.h"
# include "trash.h"
# include "utils.h"

// all other .h files
struct s_file_list;
struct s_file_list;
struct s_cmd_node;
struct s_file_node;

extern volatile sig_atomic_t	g_signal_status;

# define PATH_MAX 4096

#endif