/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaraogl <hkaraogl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 15:32:03 by tjkruger          #+#    #+#             */
/*   Updated: 2025/12/09 15:30:25 by hkaraogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_H
# define MINISHELL_H

# include <ctype.h>
# include <stdio.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
#include <fcntl.h>
#include <signal.h>


//header files
# include "history.h"
# include "libft.h"
# include "parser.h"
# include "utils.h"
# include "environment.h"
# include "builtins.h"
# include "structs.h"
# include "lexer.h"
# include "all_free.h"
#include "signals.h"
#include "execution.h"


// all other .h files
struct s_file_list;
struct s_file_list;
struct s_cmd_node;
struct s_file_node;

extern volatile sig_atomic_t g_signal_status;


# define PATH_MAX 4096


#endif