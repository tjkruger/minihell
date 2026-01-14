/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_command_list.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjkruger <tjkruger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 14:56:57 by tjkruger          #+#    #+#             */
/*   Updated: 2026/01/14 15:05:19 by tjkruger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_cmd_type(char **cmd)
{
	if (!cmd)
		return (0);
	if (ft_strcmp(cmd[0], "echo") == 0)
		return (1);
	if (ft_strcmp(cmd[0], "cd") == 0)
		return (1);
	if (ft_strcmp(cmd[0], "pwd") == 0)
		return (1);
	if (ft_strcmp(cmd[0], "export") == 0)
		return (1);
	if (ft_strcmp(cmd[0], "unset") == 0)
		return (1);
	if (ft_strcmp(cmd[0], "env") == 0)
		return (1);
	if (ft_strcmp(cmd[0], "exit") == 0)
		return (1);
	return (0);
}

int	handle_token(t_ms *ms, t_one_command *cmd)
{
	if (ms->token->type == TOKEN_WORD)
		add_word_to_cmd(cmd, ms->token->value, &ms->trash);
	else if (ms->token->type == TOKEN_REDIR_IN
		|| ms->token->type == TOKEN_REDIR_OUT
		|| ms->token->type == TOKEN_REDIR_APPEND
		|| ms->token->type == TOKEN_REDIR_HEREDOC)
	{
		if (!ms->token->next || ms->token->next->type != TOKEN_WORD)
			return (0);
		add_file_to_cmd(ms, ms->token->next->value, ms->token->type,
			ms->token->next->dna);
		ms->token = ms->token->next;
	}
	return (1);
}

int	finalize_command(t_one_command *cmd)
{
	if (!cmd->cmd && !cmd->files)
		return (0);
	if (cmd->cmd)
	{
		cmd->cmd_type = find_cmd_type(cmd->cmd);
		cmd->executable = find_executable(cmd->cmd[0]);
	}
	return (1);
}

int	parse_one_command(t_ms *ms, t_all_commands *cmd_list)
{
	t_one_command	*cmd;

	cmd = create_new_command_node(&ms->trash);
	if (!cmd)
		return (0);
	ms->curr_cmd = cmd;
	while (ms->token && ms->token->type != TOKEN_PIPE)
	{
		if (!handle_token(ms, cmd))
			return (0);
		ms->token = ms->token->next;
	}
	ms->curr_cmd = NULL;
	if (!finalize_command(cmd))
		return (0);
	add_cmd_to_list(cmd_list, cmd);
	if (ms->token && ms->token->type == TOKEN_PIPE)
		ms->token = ms->token->next;
	return (1);
}

t_all_commands	*build_commands(t_ms *ms)
{
	t_all_commands	*cmd_list;

	if (!ms)
		return (NULL);
	cmd_list = create_new_commands_list(&ms->trash);
	if (!cmd_list)
		return (NULL);
	while (ms->token)
	{
		if (!parse_one_command(ms, cmd_list))
			return (NULL);
	}
	return (cmd_list);
}
