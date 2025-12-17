/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trash.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaraogl <hkaraogl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 16:43:47 by hkaraogl          #+#    #+#             */
/*   Updated: 2025/12/17 16:23:25 by hkaraogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRASH_H
# define TRASH_H

void trash_init(t_trash *trash);
void *gc_malloc(t_trash *trash, size_t count, size_t size);
char *gc_strdup(t_trash *trash, const char *s);
char *gc_substr(t_trash *trash, const char *s, unsigned int start, size_t len);
char **gc_split(t_trash *trash, char *s, char c);
char *gc_strjoin(t_trash *trash, char const *s1, char const *s2);


void gc_add(t_trash *trash ,void *ptr);
// void gc_remove(void *ptr);
void gc_cleanup(t_trash *trash);

//debug
void gc_print(t_trash *trash);

#endif