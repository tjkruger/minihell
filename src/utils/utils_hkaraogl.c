/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_hkaraogl.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaraogl <hkaraogl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 13:40:50 by hkaraogl          #+#    #+#             */
/*   Updated: 2025/12/11 18:51:21 by hkaraogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include    "minishell.h"

int	error_exit(char *cmd, char*msg, int code)
{
	print_cmd_error(cmd, msg);
	return code;
}

void print_cmd_error(char *cmd, char *msg)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(msg, 2);
}

void	ft_perror(char *msg)
{
	ft_putstr_fd("minishell: ", 2);
	perror(msg);
}

int	error_exit_perror(char *context, int code)
{
	ft_perror(context);
	return code;
}

int ft_strcmp(char *s1, char *s2)
{
	int i = 0;

	while(s1[i]  != '\0' && s2[i] != '\0')
	{
		if(s1[i] != s2[i])
			return s1[i] - s2[i];
		i++;
	}

	return s1[i] - s2[i];
}

int	strncmp_strlen(char *s1, char *s2)
{
	int str_len = ft_strlen(s1);
	return ((str_len == ft_strlen(s2)) && (ft_strncmp(s1, s2, str_len) == 0));
}

int count_array_string(char **arr)
{
	int i = 0;

	while(arr[i])
		i++;
	return i;
}

void	free_str_arr(char **arr)
{
	int i;

	if(!arr)
		return ;
	i = 0;
	while(arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

int	is_valid_identifier(char *str)
{
	int i;

	if (!str || !str[0])
		return (0);
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

char *has_equal(char *str)
{
	char *equal;
	equal = ft_strchr(str, '=');
	return equal;
}

void print_all_cmd(t_all_commands *cmd_lst)
{
	t_one_command *current = cmd_lst->head;
	int index = 0;

	while (current)
	{
		printf("Command %d:\n", index);
		for (int i = 0; current->cmd[i] != NULL; i++)
		{
			printf("  arg[%d]: %s\n", i, current->cmd[i]);
		}
		current = current->next;
		index++;
	}
}

int validate_command(t_one_command *cmd)
{
	if (!cmd || !cmd->cmd || !cmd->cmd[0])
		return 0;
	return 1;
}