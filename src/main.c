
#include "minishell.h"

int main(void)
{
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
                add_to_hist_list(&history_list, input);
                add_history(input);// put later out if i can test with different commands then history
                print_history(history_list);
            }
            else
            {
                add_to_hist_list(&history_list, input);
                add_history(input); // only store real commands
                // TODO: here you would normally parse & execute the command
            }
        }
        free(input);
    }

    free_hist(history_list);
    return 0;
}

