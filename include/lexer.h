/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaraogl <hkaraogl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 15:31:51 by tjkruger          #+#    #+#             */
/*   Updated: 2025/12/12 16:54:53 by hkaraogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef LEXER_H
#define LEXER_H


#include <stdlib.h>
#include <stdio.h>



t_token     *tokenize(char *input);
int         token_length(char *str_start, char *str_end);
char        *pos_of_token_end(char *str, char delimiter);
int         ft_isspace(char c);
void        token_error(void);
int         how_many_token(char *str);
t_pretoken  *ft_split_for_token(char *input);
void    handle_expansions(t_token *token_list, t_env_list *env);
int is_var_char(char c);
char *ft_argument(char *str);
char    *ft_expand(char *arg, t_env_list *env);
static int  calculate_result_len(char *str, char *new, int how_much);
static void fill_result(char *result, char *str, char *new, int pos_in_str, int how_much);
char    *insert_expandet(char *str, char *new, int pos_in_str, int how_much);
char *exit_state_to_str(int exit_state);

#endif
