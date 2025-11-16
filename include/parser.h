



#ifndef PARSER_H
# define PARSER_H

#include "structs.h"


t_one_command   *create_new_command_node(void);
void    add_word_to_cmd(t_one_command *curr_cmd, char *value);
void add_cmd_to_list(t_all_commands *cmd_list, t_one_command *curr_cmd);
int is_redirection(t_token *token);
void    add_file_to_cmd(t_one_command *curr_cmd, char *value);
t_all_commands  build_commands(t_token *tokens);

#endif

