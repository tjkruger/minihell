/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjkruger <tjkruger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 15:31:51 by tjkruger          #+#    #+#             */
/*   Updated: 2025/11/27 14:45:46 by tjkruger         ###   ########.fr       */
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


#endif
