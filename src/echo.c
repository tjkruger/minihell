#include    "minishell.h"

void    run_echo(char **tokens)
{
    int i;
    i = 1;
    while(tokens[i] != NULL)
    {
        printf("%s", tokens[i]);
        if(tokens[i+1] != NULL)
            printf(" ");
        i++;
    }
    printf("\n");
}