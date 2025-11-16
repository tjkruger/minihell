
#include "minishell.h"

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
		free(input);
	}

	//free everything
	return 0;
}

