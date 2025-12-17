/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaraogl <hkaraogl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 15:50:25 by hkaraogl          #+#    #+#             */
/*   Updated: 2025/12/17 15:24:02 by hkaraogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include    "minishell.h"


int    run_cd(t_trash *trash, char **args, t_env_list *env)
{
	char *path;
	char cwd[PATH_MAX];

	if(!args[1])
		path = get_env_value(env, "HOME");
	else
		path = args[1];
	if(getcwd(cwd, sizeof(cwd)))
		set_env_value(trash, env, "OLDPWD", cwd, 1);
	if(chdir(path) != 0)
	{
		perror("cd failed");
		return 1;
	}
	if(getcwd(cwd, sizeof(cwd)))
	{
		set_env_value(trash, env, "PWD", cwd, 1);
	}
	return 0;
}