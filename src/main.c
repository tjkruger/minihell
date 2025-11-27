
#include "minishell.h"

// int main(void)
// {
// 	t_history *history_list = NULL;
// 	char *input;

// 	while (1)
// 	{
		
// 		input = readline("minishell> ");
// 		if (!input)
// 			break;

// 		if (!is_empty_or_whitespace(input))
// 		{
// 			if (strcmp(input, "history") == 0)
// 			{
// 				add_to_hist_list(&history_list, input);
// 				add_history(input);// put later out when i can test with different commands then history
// 				print_history(history_list);
// 			}
// 			else
// 			{
// 				add_to_hist_list(&history_list, input);
// 				add_history(input);
// 				what_to_do_with_tokens(get_tokens(input));
// 			}
// 		}
// 		free(input);
// 	}

// 	free_hist(history_list);
// 	return 0;
// }

// Helper functions to create test structures


void print_env_list(t_env_list *env)
{
    t_env_node *current;
    int i = 0;

    if (!env)
    {
        printf("Environment list is NULL\n");
        return;
    }
    printf("\n=== Environment List (size: %zd) ===\n", env->size);
    current = env->head;
    while (current)
    {
        printf("[%d] %s=%s\n", i++, current->key, current->value);
        current = current->next;
    }
    printf("================================\n\n");
}

#include "minishell.h"
#include <readline/readline.h>
#include <readline/history.h>

// Helper functions to create test structures
t_cmd_node *create_cmd_node(char **cmd)
{
    t_cmd_node *node = malloc(sizeof(t_cmd_node));
    if (!node)
        return NULL;
    node->cmd_type = BUILTIN;
    node->cmd = cmd;
    node->files = NULL;
    node->next = NULL;
    return node;
}

void    print_args(char **args)
{
    int i = 0;
    printf("{");
    while(args[i])
    {
        printf("\"%s\" ", args[i]);
        i++;
    }
    printf("}\n");
}

char **split_input(char *input)
{
    char **args = malloc(sizeof(char *) * 100);
    if (!args)
        return NULL;
    int i = 0;
    char *token = strtok(input, " \t\n");
    
    while (token != NULL)
    {
        args[i] = strdup(token);
        i++;
        token = strtok(NULL, " \t\n");
    }
    args[i] = NULL;
    return args;
}

void free_args(char **args)
{
    if (!args)
        return;
    int i = 0;
    while (args[i])
    {
        free(args[i]);
        i++;
    }
    free(args);
}

void print_env(t_env_list *env)
{
    if (!env)
    {
        printf("Error: env is NULL\n");
        return;
    }
    
    if (!env->head)
    {
        printf("(empty environment)\n");
        return;
    }
    
    t_env_node *current = env->head;
    while (current)
    {
        if (current->key && current->value)
            printf("%s=%s\n", current->key, current->value);
        current = current->next;
    }
}

int execute_builtin(char **args, t_env_list *env)
{
    if (!args || !args[0])
        return 0;
    if (strcmp(args[0], "cd") == 0)
        return run_cd(args, env);
    else if (strcmp(args[0], "echo") == 0)
    {
        t_cmd_node *node = create_cmd_node(args);
        if (!node)
            return 1;
        int ret = run_echo(node);
        free(node);
        return ret;
    }
    else if (strcmp(args[0], "pwd") == 0)
        return run_pwd();
    else if (strcmp(args[0], "unset") == 0)
        return run_unset(args, env);
    else if (strcmp(args[0], "export") == 0)
    {
        run_export(env, args);
        return 0;
    }
    else if (strcmp(args[0], "env") == 0)
    {
        run_env(env);
        return 0;
    }
    else if (strcmp(args[0], "exit") == 0)
    {
        run_exit(args, 1);
    }
    else
    {
        printf("Command not found: %s\n", args[0]);
        return 127;
    }
}

void cleanup_env(t_env_list *env)
{
    if (!env)
        return;
    
    t_env_node *current = env->head;
    while (current)
    {
        t_env_node *tmp = current;
        current = current->next;
        if (tmp->key)
            free(tmp->key);
        if (tmp->value)
            free(tmp->value);
        free(tmp);
    }
    free(env);
}

int main(int argc, char **argv, char **env)
{
    char *input;
    char **args;
    int exit_status;
    t_env_list *env_lst;
    
    (void)argc;
    (void)argv;
    
    // Initialize environment from system env
    env_lst = init_environment(env);
    if (!env_lst)
    {
        printf("Failed to initialize environment\n");
        return 1;
    }
    
    printf("=== Minishell Builtin Tester ===\n");
    printf("Available commands: cd, echo, pwd, unset, export, env, exit\n");
    printf("Type 'exit' to quit\n\n");
    
    while (1)
    {
        input = readline("minishell> ");
        
        if (!input)
        {
            printf("\n");
            break;
        }
        
        if (*input)
            add_history(input);
        
        args = ft_split(input, ' ');
        if (args)
        {
            exit_status = execute_builtin(args, env_lst);
            printf("Exit status: %d\n", exit_status);
            free_args(args);
        }
        
        free(input);
    }
    
    // Cleanup
    cleanup_env(env_lst);
    
    return 0;
}




// testing environment
// #include "minishell.h"

// // Hilfsfunktion zum Freigeben des Arrays
// void free_env_array(char **env_array)
// {
//     int i = 0;
//     if (!env_array)
//         return;
//     while (env_array[i])
//     {
//         free(env_array[i]);
//         i++;
//     }
//     free(env_array);
// }

// // Hilfsfunktion zum Freigeben der Liste
// void free_env_list(t_env_list *env)
// {
//     t_env_node *current;
//     t_env_node *next;

//     if (!env)
//         return;
//     current = env->head;
//     while (current)
//     {
//         next = current->next;
//         free(current->key);
//         free(current->value);
//         free(current);
//         current = next;
//     }
//     free(env);
// }

// // Hilfsfunktion zum Ausgeben der Liste
// void print_env_list(t_env_list *env)
// {
//     t_env_node *current;
//     int i = 0;

//     if (!env)
//     {
//         printf("Environment list is NULL\n");
//         return;
//     }
//     printf("\n=== Environment List (size: %zd) ===\n", env->size);
//     current = env->head;
//     while (current)
//     {
//         printf("[%d] %s=%s\n", i++, current->key, current->value);
//         current = current->next;
//     }
//     printf("================================\n\n");
// }

// int main(int argc, char **argv, char **envp)
// {
//     t_env_list *env;
//     char **env_array;
//     char *value;
//     char *cmd_path;
//     int i;

//     (void)argc;
//     (void)argv;

//     printf("=== MINISHELL ENVIRONMENT TESTER ===\n\n");

//     // Test 1: init_environment
//     printf("TEST 1: Initialisiere Environment aus system_env\n");
//     env = init_environment(envp);
//     if (!env)
//     {
//         printf("❌ Fehler: init_environment fehlgeschlagen\n");
//         return (1);
//     }
//     printf("✅ Environment initialisiert\n");
//     print_env_list(env);

//     // Test 2: get_env_value
//     printf("TEST 2: Teste get_env_value\n");
//     value = get_env_value(env, "PATH");
//     printf("PATH = %s\n", value ? value : "NULL");
//     value = get_env_value(env, "HOME");
//     printf("HOME = %s\n", value ? value : "NULL");
//     value = get_env_value(env, "USER");
//     printf("USER = %s\n", value ? value : "NULL");
//     value = get_env_value(env, "NICHT_EXISTIERT");
//     printf("NICHT_EXISTIERT = %s\n\n", value ? value : "NULL");

//     // Test 3: set_env_value (neue Variable)
//     printf("TEST 3: Teste set_env_value (neue Variable)\n");
//     set_env_value(env, "MY_VAR", "test_value");
//     value = get_env_value(env, "MY_VAR");
//     printf("MY_VAR = %s\n", value ? value : "NULL");
//     if (value && strcmp(value, "test_value") == 0)
//         printf("✅ Neue Variable erfolgreich gesetzt\n\n");
//     else
//         printf("❌ Fehler beim Setzen der neuen Variable\n\n");

//     // Test 4: set_env_value (existierende Variable überschreiben)
//     printf("TEST 4: Teste set_env_value (Variable überschreiben)\n");
//     set_env_value(env, "MY_VAR", "new_value");
//     value = get_env_value(env, "MY_VAR");
//     printf("MY_VAR = %s\n", value ? value : "NULL");
//     if (value && strcmp(value, "new_value") == 0)
//         printf("✅ Variable erfolgreich überschrieben\n\n");
//     else
//         printf("❌ Fehler beim Überschreiben der Variable\n\n");

//     // Test 5: find_command_path
//     printf("TEST 5: Teste find_command_path\n");
//     cmd_path = find_command_path("ls", envp);
//     printf("Pfad für 'ls': %s\n", cmd_path ? cmd_path : "NULL");
//     free(cmd_path);
    
//     cmd_path = find_command_path("cat", envp);
//     printf("Pfad für 'cat': %s\n", cmd_path ? cmd_path : "NULL");
//     free(cmd_path);
    
//     cmd_path = find_command_path("/usr/bin/cat", envp);
//     printf("Pfad für '/bin/echo' (absolut): %s\n", cmd_path ? cmd_path : "NULL");
//     free(cmd_path);
    
//     cmd_path = find_command_path("nicht_existierender_befehl", envp);
//     printf("Pfad für 'nicht_existierender_befehl': %s\n", cmd_path ? cmd_path : "NULL");
//     free(cmd_path);
//     printf("\n");

//     // Test 6: env_list_array
//     printf("TEST 6: Teste env_list_array (Konvertierung zu Array)\n");
//     env_array = env_list_array(env);
//     if (!env_array)
//     {
//         printf("❌ Fehler: env_list_array fehlgeschlagen\n");
//     }
//     else
//     {
//         printf("✅ Array erstellt. Erste 5 Einträge:\n");
//         for (i = 0; i < 5 && env_array[i]; i++)
//             printf("  [%d] %s\n", i, env_array[i]);
//         printf("\n");
//         free_env_array(env_array);
//     }

//     // Test 7: unset_env_value
//     printf("TEST 7: Teste unset_env_value\n");
//     printf("Größe vor unset: %zd\n", env->size);
//     unset_env_value(env, "MY_VAR");
//     printf("Größe nach unset: %zd\n", env->size);
//     value = get_env_value(env, "MY_VAR");
//     printf("MY_VAR nach unset: %s\n", value ? value : "NULL");
//     if (!value || strcmp(value, "new_value") != 0)
//         printf("✅ Variable erfolgreich gelöscht\n\n");
//     else
//         printf("❌ Fehler beim Löschen der Variable\n\n");

//     // Test 8: unset_env_value (nicht existierende Variable)
//     printf("TEST 8: Teste unset_env_value (nicht existierend)\n");
//     ssize_t size_before = env->size;
//     unset_env_value(env, "NICHT_DA");
//     printf("Größe vorher: %zd, nachher: %zd\n", size_before, env->size);
//     if (size_before == env->size)
//         printf("✅ Größe unverändert (korrekt)\n\n");
//     else
//         printf("❌ Größe hat sich geändert (falsch)\n\n");

//     // Test 9: find_env_node
//     printf("TEST 9: Teste find_env_node\n");
//     t_env_node *node = find_env_node(env, "PATH");
//     if (node)
//         printf("✅ PATH gefunden: %s=%s\n", node->key, node->value);
//     else
//         printf("❌ PATH nicht gefunden\n");
    
//     node = find_env_node(env, "NICHT_DA");
//     if (!node)
//         printf("✅ NICHT_DA korrekt nicht gefunden\n\n");
//     else
//         printf("❌ NICHT_DA fälschlicherweise gefunden\n\n");

//     // Finale Ausgabe
//     print_env_list(env);

//     // Cleanup
//     free_env_list(env);
//     printf("✅ Alle Tests abgeschlossen und Speicher freigegeben\n");

//     return (0);
// }