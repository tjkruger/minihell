/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaraogl <hkaraogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 13:45:15 by hkaraogl          #+#    #+#             */
/*   Updated: 2025/11/11 16:53:19 by hkaraogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
#define UTILS_H

int count_array_string(char **arr);
void	free_str_arr(char **arr);
int	strncmp_strlen(char *s1, char *s2);
int	is_valid_identifier(char *str);
char *has_equal(char *str);
int ft_strcmp(char *s1, char *s2);

#endif