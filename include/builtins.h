#ifndef BUILTINS_H
#define BUILTINS_H


int	run_echo(t_cmd_node *cmd_node);
int    buildin_cd(char **args, t_env_list *env);
int run_pwd(void);
int run_unset(char **cmd, t_env_list *env);


#endif
