/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: r2d2 <r2d2@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 18:18:13 by hkaraogl          #+#    #+#             */
/*   Updated: 2025/12/17 22:36:06 by r2d2             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include    "minishell.h"

//must be freed by user
static char *generate_tmpfile_name(t_trash *trash)
{
	static int counter = 0;
	char *appendix;
	char *temp;

	appendix = ft_itoa(counter);
	if(!appendix)
		return NULL;
	temp = gc_strjoin(trash, "/tmp/.minishell_heredoc_", appendix);
	// free(appendix);
	counter++;
	return temp;
}

// void	cleanup_heredoc_file(char *filename)
// {
// 	if(filename)
// 	{
// 		if(unlink(filename) == -1)
// 		{
// 			perror("unlinked failed");
// 			free(filename);
// 			return;
// 		}
// 		free(filename);
// 	}
// }
// void	cleanup_heredoc_file(char *filename)
// {
// 	if(filename)
// 	{
// 		if(unlink(filename) == -1)
// 		{
// 			perror("unlinked failed");
// 			free(filename);
// 			return;
// 		}
// 		free(filename);
// 	}
// }
//iterate through cmd_lst and iterate through each nodes file lst
//unlink heredoc temp file
//this function frees the filename of the filenode and unlink (delete)  in the filelist. So be careful freeing it again somewhere else!!!!
// void	cleanup_all_heredoc_files(t_all_commands *cmd_lst)
// {
// 	t_one_command *current;
// 	t_file_node *file;
// void	cleanup_all_heredoc_files(t_all_commands *cmd_lst)
// {
// 	t_one_command *current;
// 	t_file_node *file;

// 	if(!cmd_lst || !cmd_lst->head)
// 		return;
// 	current = cmd_lst->head;
// 	while(current)
// 	{
// 		if(current->files)
// 		{
// 			file = current->files->head;
// 			while(file)
// 			{
// 				if(file->redir_type == TOKEN_REDIR_HEREDOC && file->filename)
// 				{
// 					unlink(file->filename);
// 					free(file->filename);
// 					file->filename = NULL;
// 				}
// 				file = file->next;
// 			}
// 		}
// 		current = current->next;
// 	}
// }
// 	if(!cmd_lst || !cmd_lst->head)
// 		return;
// 	current = cmd_lst->head;
// 	while(current)
// 	{
// 		if(current->files)
// 		{
// 			file = current->files->head;
// 			while(file)
// 			{
// 				if(file->redir_type == TOKEN_REDIR_HEREDOC && file->filename)
// 				{
// 					unlink(file->filename);
// 					free(file->filename);
// 					file->filename = NULL;
// 				}
// 				file = file->next;
// 			}
// 		}
// 		current = current->next;
// 	}
// }

int	no_qoutes(char *str)
{
	int i = 0;
	while(str[i])
	{
		if(str[i] == '\'' || str[i] == '\"')
			return 0;
		i++;
	}
	return 1;
}


#include <unistd.h>

// prints a single token to fd, respecting the dna string for quotes
void printout_token(int fd, char *value, char *dna)
{
    char last_mode = 0; // track current quote mode

    for (int i = 0; value[i]; i++)
    {
        if (dna[i] != last_mode)
        {
            // close previous quote if any
            if (last_mode == 'D') write(fd, "\"", 1);
            if (last_mode == 'S') write(fd, "'", 1);

            // open new quote if needed
            if (dna[i] == 'D') write(fd, "\"", 1);
            if (dna[i] == 'S') write(fd, "'", 1);

            last_mode = dna[i];
        }

        write(fd, &value[i], 1);
    }

    // close remaining quote if still open
    if (last_mode == 'D') write(fd, "\"", 1);
    if (last_mode == 'S') write(fd, "'", 1);
}

//this function will executed only if heredoc *file exists
//create tmp file,
//collect input,
//expand if needed
//save tmp file
static int	setup_heredoc(t_trash *trash, t_file_node *file, t_env_list *env_lst)
{
	t_token *temp_token_heredoc;
	t_token *tok_head;
	char *tmp_file;
	char *line;
	int fd = 0;
	tmp_file = generate_tmpfile_name(trash);
	
	fd = open(tmp_file, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if(fd == -1)
		return (perror("heredoc tmp file"), 0);

    while(1)
    {
        line = readline("heredoc:");
        if(!line)
            break;
        
        if(ft_strcmp(line, file->delimiter) == 0)
        {
            free(line);
            break;
        }
        // tokenize heredoc line: pass NULL so quotes are handled correctly
        temp_token_heredoc = tokenize(line, trash);
        if(!temp_token_heredoc)
        {
            free(line);
            close(fd);
            free(tmp_file);
            return (perror("heredoc tokenize failed"), 0);
        }
        if(!file->qoutes_in_heredoc)
            handle_expansions(temp_token_heredoc, env_lst);

        // keep head so we can free properly after iterating
        tok_head = temp_token_heredoc;
        while(temp_token_heredoc)
        {
            printout_token(fd, temp_token_heredoc->value, temp_token_heredoc->dna);
            if (temp_token_heredoc->next)
                write(fd, " ", 1);
            temp_token_heredoc = temp_token_heredoc->next;
        }
        write(fd, "\n", 1);
        free(line);
        free_token_list(tok_head);
    }
    close(fd);
    file->filename = tmp_file;
    return 1;
}

// char *handle_expansions(char *str, t_env_list *env)
// {
//     char *ex_str;
//     char *arg;
//     int   i;
//     char *new;


// 	i = 0;

// 	while (str[i] != '\0')
// 	{
// 		if (str[i] == '$' && check_for_single())//schauen ob single quotes oder nicht
// 		{
// 			arg = ft_argument(str + i + 1);
// 			if (arg && arg[0] == '?' && arg[1] == '\0')
// 				ex_str = exit_state_to_str(env->last_exit);
// 			else
// 				ex_str = ft_expand(arg, env);
// 			if (!ex_str)
// 				ex_str = "";

// 			new = insert_expandet(str, ex_str, i, ft_strlen(arg) + 1);
// 			free(str);
			
// 			// Move i to just after the inserted expansion
// 			i += ft_strlen(ex_str) - 1; // -1 because i++ will happen
			
// 			if (arg)
// 				free(arg);
// 		}
// 		i++;
// 	}
// 	return(new);
// }

int setup_all_heredoc(t_trash *trash, t_all_commands *cmd_lst, t_env_list *env_lst)
{
	t_one_command *current;
	t_file_node *file;

	current = cmd_lst->head;
	while(current)
	{
		if(current->files && current->files->head)
		{
			file = current->files->head;
			while(file)
			{
				if(file->redir_type == TOKEN_REDIR_HEREDOC)
				{
					if(!setup_heredoc(trash, file, env_lst))
						return 0;
				}
				file = file->next;
			}
		}
		current = current->next;
	}
	return 1;
}