/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: r2d2 <r2d2@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 15:31:51 by tjkruger          #+#    #+#             */
/*   Updated: 2025/11/24 15:50:16 by r2d2             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef LEXER_H
#define LEXER_H


#include <stdlib.h>
#include <stdio.h>



t_token *tokenize(char *input);
int     token_length(char *str_start, char *str_end);
char    *pos_of_token_end(char *str, char delimiter);
int     ft_isspace(char c);
void    token_error(void);
int     how_many_token(char *str);
char    **ft_split_for_token(char *input);


#endif
