#ifndef FT_VALIDATIONS_H
# define FT_VALIDATIONS_H

# include "../minishell.h"

// validations

// check if the command is empty
bool	is_empty(char *command);

// check if the command is a built-in command
bool	is_builtin(char *cmd);

// check if the command is valid
bool	validate_command(char *command);

// commanmd checker

// check for path
char	*checkforpath(char *cmd, t_env *env);

// check if command sent is in path format
bool	is_command_path(char *cmd);

#endif