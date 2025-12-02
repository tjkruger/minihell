

#include "minishell.h"

int is_var_char(char c) 
{
    return (c != '\0' && c != ' ' && c != '|' && c != '>' && c != '<');
}
char    *ft_argument(char *str)
{
    char *new;
    int len;
    int i;

    len = 0;
    i = 0;
    new = NULL;
    str++;
    while(is_var_char(str[len]))
        len++;
    new = malloc(sizeof(char) * (len + 1));
    while(len > i)
    {
        new[i] = str[i];
        i++;
    }
    new[i] = '\0';

    return(new);
}

char    *ft_expand(char *arg)
{
    char *new;

    //find out if the variable exists or so i dont know somehow also put this in a loop idek
    
    return(new);
}

static int  calculate_result_len(char *str, char *new, int how_much)
{
    int str_len;
    int new_len;

    str_len = 0;
    while (str[str_len])
        str_len++;
    
    new_len = 0;
    while (new[new_len])
        new_len++;
    
    return (str_len - how_much + new_len);
}

static void fill_result(char *result, char *str, char *new, int pos_in_str, int how_much)
{
    int i;
    int j;
    int str_len;

    str_len = 0;
    while (str[str_len])
        str_len++;
    
    i = 0;
    while (i < pos_in_str && i < str_len)
    {
        result[i] = str[i];
        i++;
    }
    
    j = 0;
    while (new[j])
    {
        result[i] = new[j];
        i++;
        j++;
    }
    
    j = pos_in_str + how_much;
    while (j < str_len)
    {
        result[i] = str[j];
        i++;
        j++;
    }
    
    result[i] = '\0';
}

char    *insert_expandet(char *str, char *new, int pos_in_str, int how_much)
{
    char    *result;
    int     result_len;

    if (!str || !new || pos_in_str < 0)
        return (NULL);
    
    result_len = calculate_result_len(str, new, how_much);
    
    result = (char *)malloc(sizeof(char) * (result_len + 1));
    if (!result)
        return (NULL);
    
    fill_result(result, str, new, pos_in_str, how_much);
    
    return (result);
}

void    handle_expansions(t_token *token_list)
{
    char *ex_str;
    char *str;
    char *arg;
    int i;
    
    str = NULL;
    ex_str = NULL;
    arg = NULL;
    while(token_list)
    {
        i = 0;
        str = token_list->value;
        while(str[i] != '\0')
        {
            if(str[i] == '$' && token_list->dna[i] != 'S')
            {
                arg = ft_argument(str + i);
                if(arg)
                    ex_str = ft_expand(arg);
                if(!ex_str)
                    ex_str = "";
                str = insert_expandet(str, ex_str, i, ft_strlen(arg + 1));
                i--;
            }
            i++;
        }
        token_list = token_list->next;
    }
    
}