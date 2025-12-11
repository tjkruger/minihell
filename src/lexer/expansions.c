

#include "minishell.h"

int is_var_char(char c) 
{
    return (c != '\0' && c != ' ' && c != '|' && c != '>' && c != '<' && c != '$');
}

char *ft_argument(char *str)
{
    char *new;
    int len = 0;
    while (is_var_char(str[len]))
        len++;
    new = malloc(sizeof(char) * (len + 1));
    for (int i = 0; i < len; i++)
        new[i] = str[i];
    new[len] = '\0';
    return new;
}


char    *ft_expand(char *arg, t_env_list *env)
{
    char *new;
    new = get_env_value(env, arg);

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
    int i = 0;
    int j = 0;

    j = 0;
    while (j < pos_in_str)
    {
        result[i] = str[j];
        i++;
        j++;
    }
    j = 0;
    while (new[j])
    {
        result[i] = new[j];
        i++;
        j++;
    }
    j = pos_in_str + how_much;
    while (str[j])
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

char *exit_state_to_str(int exit_state)
{
    char *str;
    str = ft_itoa(exit_state);
    return(str);
}

void handle_expansions(t_token *token_list, t_env_list *env)
{
    char *ex_str;
    char *str;
    char *arg;
    int   i;
    char *new;

    while (token_list)
    {
        str = token_list->value;
        i = 0;

        while (str[i] != '\0')
        {
            if (str[i] == '$' && token_list->dna[i] != 'S')
            {
                arg = ft_argument(str + i + 1);
                if (arg && arg[0] == '?' && arg[1] == '\0')
                    ex_str = exit_state_to_str(env->last_exit);
                else
                    ex_str = ft_expand(arg, env);
                if (!ex_str)
                    ex_str = "";

                new = insert_expandet(str, ex_str, i, ft_strlen(arg) + 1);
                free(str);
                str = new;
                token_list->value = str;
                
                // Move i to just after the inserted expansion
                i += ft_strlen(ex_str) - 1; // -1 because i++ will happen
                
                if (arg)
                    free(arg);
            }
            i++;
        }
        token_list = token_list->next;
    }
}


