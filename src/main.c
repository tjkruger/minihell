
#include "minishell.h"


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <ctype.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <ctype.h>

int is_empty_or_whitespace(const char *s)
{
    if (!s) 
        return 1;
    while (*s)
    {
        if (!isspace((unsigned char)*s)) 
            return 0;
        s++;
    }
    return 1;
}

void print_history()
{
    HIST_ENTRY **the_list = history_list(); // need to get my own bc this is not allowed ig
    if (!the_list) 
        return;

    for (int i = 0; the_list[i]; i++)
        printf("%d  %s\n", i + history_base, the_list[i]->line);// wtf is history space ?? wo kommt das her ? prolly start von dem hist_entry
}

int main(void)
{
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
                add_history(input);// need a filter for the real commands
                print_history();
            }
            else
            {
                add_history(input); // only store real commands
                // TODO: here you would normally parse & execute the command
            }
        }

        free(input);
    }

    rl_clear_history(); // free readline's internal history at exit
    return 0;
}

