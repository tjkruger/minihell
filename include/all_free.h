

#ifndef ALL_FREE_H
# define ALL_FREE_H

#include "structs.h"

void free_cmd_list(t_all_commands *cmds);
void free_file_list(t_file_list *files);
void free_token_list(t_token *head);
void free_hist(t_history *history_list);



#endif