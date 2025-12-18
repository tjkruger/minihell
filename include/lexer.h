/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjkruger <tjkruger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 15:31:51 by tjkruger          #+#    #+#             */
/*   Updated: 2025/12/18 14:15:55 by tjkruger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef LEXER_H
#define LEXER_H

int is_op(char c);
int make_op_token(t_token **head,char *str,char *dna, int i, t_trash *trash);
int is_var_char(char c);
int validate_token(t_token  *head);
int token_length(char *str_start, char *str_end);
int ft_isspace(char c);
int is_specialchar(char c);
int how_many_token(char *str);
char    *insert_expandet(char *str, char *new, int pos_in_str, int how_much, t_trash *trash);
char    *find_token_end(char *str);
char    *ft_strjoin_free(char *s1, char c, t_trash *trash);
char    *append_char(char *s, char c, t_trash *trash);
char    **extracted_token(char *str, t_trash *trash);
char    *exit_state_to_str(int exit_state);
char    *ft_argument(char *str, t_trash *trash);
char    *ft_expand(char *arg, t_env_list *env);
void    push_token(t_token **head, char *value, char *dna, t_trash *trash);
void    token_error(void);
void    flush_word(t_token **head, char **txt_buf, char **dna_buf, t_trash *trash);
void    handle_expansions(t_token *token_list, t_env_list *env, t_trash *trash);
static void fill_result(char *result, char *str, char *new, int pos_in_str, int how_much);
static int  calculate_result_len(char *str, char *new, int how_much);
t_token *tokenize(char *input, t_trash *trash);
t_token *split_pretoken(char *text, char *dna, t_trash *trash);
t_pretoken  *ft_split_for_token(char *input, t_trash *trash);
t_token_type    get_token_type(char *str);

#endif
