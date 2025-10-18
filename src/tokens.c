#include "minishell.h"


char    **get_tokens(char *line)
{
    char    **tokens;
    tokens = ft_split(line);
    return(tokens);
}

void    what_to_do_with_tokens(char **tokens)
{
    if (!tokens || !tokens[0])
        return;
    if ( )
}