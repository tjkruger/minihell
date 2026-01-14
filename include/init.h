/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaraogl <hkaraogl@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 17:53:32 by hkaraogl          #+#    #+#             */
/*   Updated: 2026/01/14 12:55:32 by hkaraogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_H
# define INIT_H

//init_environment.c
t_env_list	*init_environment(char **system_env);

//init.c
void init_shell_level(t_ms *ms);



#endif