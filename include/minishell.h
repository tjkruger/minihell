/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaraogl <hkaraogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 15:32:03 by tjkruger          #+#    #+#             */
/*   Updated: 2025/11/27 17:35:23 by hkaraogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_H
# define MINISHELL_H

# include <ctype.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
#include <fcntl.h>

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


// all other .h files
struct s_file_list;
struct s_file_list;
struct s_cmd_node;
struct s_file_node;


# define PATH_MAX 4096


#endif