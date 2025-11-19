/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaraogl <hkaraogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 15:50:25 by hkaraogl          #+#    #+#             */
/*   Updated: 2025/11/11 16:54:26 by hkaraogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include    "minishell.h"


int    run_cd(char **args, t_env_list *env)
{
	char *path;
	char cwd[PATH_MAX];

	if(!args[1])
		path = get_env_value(env, "HOME");
	else
		path = args[1];
	if(getcwd(cwd, sizeof(cwd)))
		set_env_value(env, "OLDPWD", cwd);
	if(chdir(path) != 0)
	{
		perror("cd failed");
		exit(1);
	}
	if(getcwd(cwd, sizeof(cwd)))
	{
		set_env_value(env, "PWD", cwd);
	}
	return 0;
}