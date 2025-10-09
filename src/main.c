
#include "minishell.h"


t_mycommands g_mycommands[] = 
{
	{"history", my_history},
	{NULL, NULL}
};



void    distribution_center(char *input, t_shell *shell)
{
    //function for splitting up the tokens and filtering out the noncommands
    int i;
    i = 0;

    while(g_mycommands[i].name)
    {
        if (strcmp(input, g_mycommands[i].name) == 0)
        {
            g_mycommands[i].func(NULL, shell);
            return;
        }
        i++;
    }
}

int main()
{
    t_shell shell = {NULL, NULL};
    char *input;

    printf("hello there\n");

    while (1)
    {
        input = readline("minishell> ");
        if (!input)
            break;
        //filter all the junk
        add_to_history(input, &shell.head, &shell.tail);
        distribution_center(input, &shell);
        free(input);
    }
    free_myhistory(shell.head);
    return 0;
}