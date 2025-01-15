/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneves-a <nneves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 18:01:28 by joamiran          #+#    #+#             */
/*   Updated: 2025/01/15 21:18:27 by nneves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_H
# define MINISHELL_H

# include "../inc/lib_ft/ft_printf.h"
# include "../inc/lib_ft/get_next_line.h"
# include "../inc/lib_ft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# ifndef PATH_MAX
#  define PATH_MAX 4096 
// Maximum number of bytes in a pathname
//Typical maximum path length in many systems
// getconf PATH_MAX / to determine the actual limit for your system.
# endif

# define monke "\U0001F648"

# define PROMPT monke " minishell _$ "
# define PROMPT_SIZE 11

# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"
# define MAGENTA "\033[0;35m"
# define CYAN "\033[0;36m"
# define RESET "\033[0m"

# define HERE_DOC "here_doc"
# define HD_TEMP_FILE ".hd_temp"
# define HISTORY ".minishell_history"

typedef enum	e_exit_status
{
	EXITSUCCESS = 0,	// Successful execution
	EXITFAILURE = 1,	// General failure (often used by programs to indicate an error)

	// Shell-specific exit codes (for shell-like environments)
	EXIT_COMMAND_NOT_FOUND = 127,  // Command not found (shell scripts)

	SIG = 128 //+ SIGSEGV,			// + signal - For all the other SIG's 
}	t_exit_status;

// struct to store the here document information
typedef struct here_doc
{
	char *delim;                // delimiter of the here document
	char *content;              // content of the here document
	char *file;                 // file to store the here document

	int fd;                     // file descriptor
}				t_here_doc;

// struct to store the redirection information
typedef struct redir
{
	char *input;                // input redirection
	char *output;               // output redirection
	char *error;                // error redirection
	char *here_doc;             // here document
}				t_redir;

// struct to store the command information
typedef struct cmd
{
	char *name;                 // command name
	char **args;                // arguments
	char *path;                 // path to the command, precisamos disto?se so usamos exclusivamente os builtins ja predefinidos.

	struct cmd *next;           // next command
	struct cmd *prev;           // previous command

	t_redir **redirs;           // redirections

}				t_cmd;

// struct to store the file descriptors
typedef struct fds
{
	int fd_in;                  // file descriptor for the input
	int fd_out;                 // file descriptor for the output
	int fd_err;                 // file descriptor for the error
	int fd_here_doc;            // file descriptor for the here document
}				t_fds;

// struct to store the environment variable and its value
typedef struct env_var
{
	char *key;                  // environment variable
	char *value;                // value of the environment variable
	bool exported; 				// if only 'a' goes to export only, if a= goes to env aswell
	struct env_var *next;       // next environment variable
	struct env_var *prev;       // previous environment variable
}				t_env_var;

// struct to store the environment variables
typedef struct env
{
	t_env_var *head;            // head of the environment variables
	t_env_var *last;            // last of the environment variables
}				t_env;

// struct to store the shell information
typedef struct shell
{
	t_here_doc	*hd;

	t_env	*env;                 // environment variables
	char	*line;                 // line read from the input
	char	*history_file;         // file to store the history

	char	**tokens;              // tokens from the line

	int ret;                    // return value
	int status;                 // status of the shell
	int exit_value;

	t_fds *fds;                 // file descriptors
	t_cmd **cmds;               // commands
}				t_shell;

// main.c
int     main(int argc, char **argv, char **env);        // main function to run the minishell program

// shell.c
void    run_shell(t_shell *shell);      // function to run the shell

// init.c
// initializes the shell struct
t_shell *init_shell(char **env);        // function to initialize the shell
void ft_print_harambe(void);           // function to print harambe

// utils.c
void    new_prompt(void);               // function to print the prompt

// parse.c
void    parse_line(t_shell *shell);     // function to parse the line
void    parse_tokens(t_shell *shell);   // function to parse the tokens
void    parse(t_shell *shell);          // function to parse the line and tokens
char **split_with_quotes(char *line);   // function to split the line with quotes
int count_quotes(char *line);           // function to count the number of quotes
char    **ft_parse_split(char *line);   // function to split the line into tokens

// signals.c
void    setup_signals(void);                                        // function to setup the signals
void    siginfo_handler(int sig, siginfo_t *info, void *context);   // function to handle the signals

// path.c

// here_doc.c

// history.c

// validations.c
bool    is_empty(char *command);                            // function to check if the command is empty
bool    is_builtin(char *command);                          // function to check if the command is a built-in command
bool    validate_command(char *command);                    // function to check if the command is valid

// free.c
void	free_array(char **array);           // function to free an array
void	close_fds(t_fds *fds);              // function to close the file descriptors
void	free_cmd(t_cmd *cmd);               // function to free a command
void	free_redir(t_redir *redirs);        // function to free a redirection
void	free_redirs(t_redir **redirs);      // function to free the redirections
void	free_cmd(t_cmd *cmd);               // function to free a command
void	free_cmds(t_cmd **cmds);            // function to free the commands
void	free_env_var(t_env_var *env_var);   // function to free an environment variable
void	free_env(t_env *env);               // function to free the environment
void    free_tokens(char **tokens);         // function to free the tokens
void	free_shell(t_shell *shell);         // function to free the shell
void	clean_exit(t_shell *shell);         // function to exit the shell

// debug.c
void    print_env(t_env *env);              // function to print the environment

// execute_command.c
void execute_command(t_cmd *cmd, t_shell *shell);    // function to execute the command

// builtins
void	cd_shell(char *cmd, t_env *env);   // function to change the directory
void	echo_shell(t_cmd *cmd);             // function to print the arguments
void	pwd_shell(void);                    // function to print the current directory
void	exit_shell(t_shell *shell);         // function to exit the shell

void export_var(char *var, t_env *env);  // function to export an environment variable
void export_no_args(t_env *env);         // function to export all environment variables
void export_bi(char *value, t_shell *shell); // function to export the environment variables


// unset
t_env_var	*find_env_var(t_env *env, char *key);       // function to find an environment variable
void		remove_env_var(t_env *env, char *key);          // function to remove an environment variable
void		unset_env_var(t_shell *shell, char *key);     // function to unset an environment variable
void		unset_vars(t_shell *shell, char **keys);       // function to unset multiple environment variables
// env.c
void	assign_env_var(t_env_var *env_var, char *env);      // function to assign an environment variable
void	add_env_var(t_env **env);                           // function to add an environment variable
t_env	*copy_env(char **env);                              // function to copy the environment
// ls.c
void	ls_shell(t_cmd *cmd);                // function to list the files in the directory

#endif
