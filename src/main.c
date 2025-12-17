/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaraogl <hkaraogl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/12/17 17:36:13 by hkaraogl         ###   ########.fr       */
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
	t_token	*token_list = NULL;
	t_all_commands *cmds = NULL;
	t_history *history_list = NULL;
	t_env_list *env_lst;
	t_trash trash;
	int i;
	int exit_status;
	char *input;
	(void)argc;
	(void)argv;
	exit_status = 0;
	env_lst = init_environment(env);

	setup_signals_interactive();
	trash_init(&trash);

	while (1)
	{
		input = readline("minishell> ");
		if (g_signal_status == 130)
		{
			exit_status = 130;
			env_lst->last_exit = exit_status;
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
				print_history(history_list);
				free(input);
				continue;
			}

			else
			{
				add_to_hist_list(&history_list, input);
				add_history(input);
			}
			token_list = tokenize(input);
			if(!token_list)
			{
				cmds = NULL;
				continue;
			}
			handle_expansions(token_list, env_lst);
			cmds 	   = build_commands(token_list);
			setup_all_heredoc(&trash, cmds, env_lst);

			exit_status = execute_commands(&trash, cmds, env_lst);
			env_lst->last_exit = exit_status;
			gc_print(&trash);
			gc_cleanup(&trash);
			gc_print(&trash);
		}
		// print_everything(token_list, cmds, history_list);//for now to test
		// print_tokens(token_list);
		free(input);
		// free_cmd_list(cmds);
		cmds = NULL;
		free_token_list(token_list);
		token_list = NULL;



	}
	free_all_environment(env_lst);
	free_hist(history_list);
	return exit_status;
}



