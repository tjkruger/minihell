/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaraogl <hkaraogl@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 15:31:51 by tjkruger          #+#    #+#             */
/*   Updated: 2026/01/14 14:57:03 by hkaraogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "structs.h"
# include "trash.h"

/* lexer/tokenizer public API */
int				is_op(char c);
int				is_op_char(char *dna, char *text, int i);
int				is_double_op(t_lexer_ctx *ctx);
int				make_double_op(t_lexer_ctx *ctx);
int				make_op_token(t_lexer_ctx *ctx);
void			make_single_op(t_lexer_ctx *ctx);

int				is_var_char(char c);
int				ft_isspace(char c);
int				is_specialchar(char c);
int				token_length(char *str_start, char *str_end);
char			*find_token_end(char *str);
int				how_many_token(char *str);

char			**extracted_token(char *str, t_trash *trash);
t_pretoken		*ft_split_for_token(char *input, t_trash *trash);
t_token			*split_pretoken(char *text, char *dna, t_ms *ms);

char			*ft_strjoin_free(char *s1, char c, t_trash *trash);
char			*append_char(char *s, char c, t_trash *trash);

void			push_token(t_token **head, char *value, char *dna,
					t_trash *trash);
void			flush_word(t_token **head, char **txt_buf, char **dna_buf,
					t_trash *trash);
void			append_subtokens(t_token **head, t_token **tail, t_token *sub);

int				validate_token(t_token *head);
t_token_type	get_token_type(char *str);

t_token			*tokenize(char *input, t_ms *ms);
t_token			*tokenize_normal(char *input, t_ms *ms);
t_token			*tokenize_heredoc(char *input, t_ms *ms);

/* expansions */
char			*insert_expandet(t_expand_ctx *ctx);
char			*exit_state_to_str(int exit_state, t_trash *trash);
char			*ft_argument(char *str, t_trash *trash);
char			*ft_expand(char *arg, t_env_list *env);
void			handle_expansions(t_token *token_list, t_env_list *env,
					t_trash *trash);

void			token_error(void);

#endif
