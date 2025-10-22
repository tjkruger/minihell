#include "minishell.h"


char    **get_tokens(char *line)
{
    char    **tokens;
    tokens = ft_split(line, ' ');
    return(tokens);
}

void    what_to_do_with_tokens(char **tokens)
{
    if (!tokens || !tokens[0])
        return;
    if (strcmp(tokens[0], "echo") == 0)
        run_echo(tokens);
    else 
        printf("please put real command i can handle stupid\n");
    //else if ()
    //else if ()
    //... all other simple inbuild command the others are coming in another function for reasons like need also multiple arguments and stuff
}