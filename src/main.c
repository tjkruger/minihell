/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: r2d2 <r2d2@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 12:39:51 by tjkruger          #+#    #+#             */
/*   Updated: 2025/11/18 14:47:41 by r2d2             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"


#include <stdio.h>
#include "minishell.h"
#include <stdio.h>
#include "minishell.h"

/* ---------------- TOKEN PRINTING ---------------- */

static void print_tokens(t_token *t)
{
    printf("\n=== TOKENS ===\n");

    while (t)
    {
        printf("Type: %d  |  Value: %s\n",
               t->type,
               t->value ? t->value : "(null)");
        t = t->next;
    }
}

/* ---------------- FILE REDIRECT PRINTING ---------------- */

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

/* ---------------- ONE COMMAND PRINTING ---------------- */

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

/* ---------------- COMMAND LIST PRINTING ---------------- */

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

/* ---------------- HISTORY PRINTING ---------------- */

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

/* ---------------- EVERYTHING PRINTING ---------------- */

void print_everything(t_token *tokens, t_all_commands *cmds, t_history *history)
{
    printf("\n\n=========================\n");
    printf("      DEBUG OUTPUT\n");
    printf("=========================\n");

    print_tokens(tokens);
    print_all_commands(cmds);
    print_history_list(history);

    printf("=========================\n\n");
}


int main(void)
{
	t_token	*token_list;
	t_all_commands *cmds;
	t_history *history_list = NULL;
	char *input;

	while (1)
	{
		input = readline("minishell> ");
		if (!input)
			break;

		if (!is_empty_or_whitespace(input))
		{
			if (strcmp(input, "history") == 0)
			{
				print_history(history_list);
			}
			else
			{
				// add_to_hist_list(&history_list, input);
				// add_history(input);


				token_list = tokenize(input);
				cmds 	   = build_commands(token_list);
				
			}
		}
		print_everything(token_list, cmds, history_list);//for now to test
		free(input);
		free_cmd_list(cmds);
		free_token_list(token_list);
	}
	free_hist(history_list);
	//free everything
	return 0;
}


//need to take care of the '' "" in the command parsing also take care of the executable flag also the expension commands need to be taken care of
