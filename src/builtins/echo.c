/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaraogl <hkaraogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 15:31:21 by hkaraogl          #+#    #+#             */
/*   Updated: 2025/11/27 17:37:52 by hkaraogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include    "minishell.h"

//tokens = {echo, -nnhnnnn, -n, Hello, World, NULL}
//echo -nnnnnnn -n -n -n Hello World


static int validate_flag(char *flag)
{
	int i;

	if(flag[0] != '-')
		return 0;
	
	i = 1;

	if(flag[i] != 'n')
		return 0;

	while(flag[i] != '\0')
	{
		if(flag[i] != 'n')
			return 0;
		i++;
	}
	return 1;
}

int	run_echo(t_one_command *cmd_node)
{
	int i;
	int newline = 1;
	i = 1;
	while(cmd_node->cmd[i] != NULL && validate_flag(cmd_node->cmd[i]))
	{
		newline = 0;
		i++;
	}

	while(cmd_node->cmd[i] != NULL)
	{
		printf("%s", cmd_node->cmd[i]);
		if(cmd_node->cmd[i + 1] != NULL)
			printf(" ");
		i++;
	}
	if(newline)
		printf("\n");
	return 0;
}
