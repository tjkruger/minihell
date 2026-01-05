/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjkruger <tjkruger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2026/01/05 17:26:56 by tjkruger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


/* ************************************************************************** */

#include "minishell.h"

/* ---------------- TOKEN PRINTING ---------------- */

static void print_tokens(t_token *t)
{
	printf("\n=== TOKENS ===\n");

	while (t)
	{
		printf("Type: %d  | DNA: %s |  Value: %s\n",
			   t->type,
			   t->dna,
			   t->value ? t->value : "(null)");
		t = t->next;
	}
}

// /* ---------------- FILE REDIRECT PRINTING ---------------- */

static void print_file_nodes(t_file_list *fl)
{
	printf("Redirect list (size: %zd):\n", fl ? fl->size : 0);

	if (!fl || !fl->head)
	{
		printf("   (no redirects)\n");
		return;
	}

	t_file_node *n = fl->head;
	while (n)
	{
		printf("   type: %d  -> file: %s\n",
			   n->redir_type,
			   n->filename ? n->filename : "(null)");
		n = n->next;
	}
}

// /* ---------------- ONE COMMAND PRINTING ---------------- */

static void print_one_cmd(t_one_command *cmd, int index)
{
	printf("\n--- COMMAND %d ---\n", index);

	printf("cmd_type: %d\n", cmd->cmd_type);
	printf("executable: %d\n", cmd->executable);

	/* Command arguments (cmd is your char **) */
	printf("Arguments:\n");
	if (!cmd->cmd)
		printf("   (none)\n");
	else
	{
		int i = 0;
		while (cmd->cmd[i])
		{
			printf("   [%d] %s\n", i, cmd->cmd[i]);
			i++;
		}
	}

	/* Redirects list */
	printf("Redirects:\n");
	print_file_nodes(cmd->files);
}

// /* ---------------- COMMAND LIST PRINTING ---------------- */

static void print_all_commands(t_all_commands *cmds)
{
	printf("\n=== COMMAND LIST ===\n");

	if (!cmds)
	{
		printf("(NULL commands struct)\n");
		return;
	}

	printf("syntax_error: %d\n", cmds->syntax_error);
	printf("size: %zd\n", cmds->size);

	t_one_command *current = cmds->head;
	int index = 0;

	while (current)
	{
		print_one_cmd(current, index);
		index++;
		current = current->next;
	}
}

// /* ---------------- HISTORY PRINTING ---------------- */

static void print_history_list(t_history *h)
{
	printf("\n=== HISTORY ===\n");

	if (!h)
	{
		printf("(empty)\n");
		return;
	}

	while (h)
	{
		printf("%s\n", h->command);
		h = h->next;
	}
}

void print_array(char **arr)
{
	if (!arr)
	{
		printf("(null array)\n");
		return;
	}

	int i = 0;
	while (arr[i])
	{
		printf("arr[%d]: %s\n", i, arr[i]);
		i++;
	}
}

// /* ---------------- EVERYTHING PRINTING ---------------- */

void print_everything(t_token *tokens, t_all_commands *cmds, t_history *history)
{
	printf("\n\n=========================\n");
	printf("      DEBUG OUTPUT\n");
	printf("=========================\n");

	print_all_commands(cmds);

	printf("=========================\n\n");
}

void free_all_environment(t_env_list *env_lst)
{
	t_env_node *current;
	t_env_node *next;

	if (!env_lst)
		return;

	current = env_lst->head;
	while (current)
	{
		next = current->next;
		free(current->key);
		free(current->value);
		free(current);
		current = next;
	}
	free(env_lst);
}

int main(int argc, char **argv, char **env)
{
	t_ms ms;
	ms.history_list = NULL;
	int i;
	int exit_status;
	char *input;
	(void)argc;
	(void)argv;
	exit_status = 0;
	ms.env_list = init_environment(env);

	setup_signals_interactive();
	trash_init(&ms.trash);

	while (1)
	{
		input = readline("minisHell> ");
		if (g_signal_status == 130)
		{
			exit_status = 130;
			ms.env_list->last_exit = exit_status;
			g_signal_status = 0;
			if (input)
				free(input);
			continue;             // ← Wichtig: Neue Iteration!
		}
		if (!input)
		{
			write(STDOUT_FILENO, "exit\n", 5);
			break;
		}
		if (!is_empty_or_whitespace(input))
		{
			if (strcmp(input, "history") == 0)
			{
				print_history(ms.history_list);
				free(input);
				continue;
			}
			else
			{
				add_to_hist_list(&ms.history_list, input);
				add_history(input);
			}
			ms.token = tokenize(input, &ms);
			if(!ms.token)
			{
				ms.all_commands = NULL;
				continue;
			}
			handle_expansions(ms.token, ms.env_list, &ms.trash);
			ms.all_commands	= build_commands(&ms);
			setup_all_heredoc(&ms);

			exit_status = execute_commands(&ms);
			ms.env_list->last_exit = exit_status;
			gc_cleanup(&ms.trash);
		}
		free(input);
		ms.all_commands = NULL;
		ms.token = NULL;
	}
	free_all_environment(ms.env_list);
	free_hist(ms.history_list);
	return exit_status;
}



