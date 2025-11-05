/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaraogl <hkaraogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 14:43:13 by hkaraogl          #+#    #+#             */
/*   Updated: 2025/11/04 15:07:52 by hkaraogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include    "minishell.h"

int run_pwd(void)
{
	char cwd[PATH_MAX];

	if(!getcwd(cwd, sizeof(cwd)))
	{
		perror("pwd");
		return 1;
	}
	printf("%s\n", cwd);
	return 0;
}