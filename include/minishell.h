/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjkruger <tjkruger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 15:32:03 by tjkruger          #+#    #+#             */
/*   Updated: 2026/01/14 15:20:21 by tjkruger         ###   ########.fr       */
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
struct	s_file_list;
struct	s_file_list;
struct	s_cmd_node;
struct	s_file_node;

# define PATH_MAX 4096

#endif