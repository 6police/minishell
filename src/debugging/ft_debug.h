#ifndef FT_DEBUG_H
# define FT_DEBUG_H

# include "../minishell.h"

// Print the enviroment variables
void	print_env(t_env *env);

// Print the exported enviroment variables
void	print_export(t_env *env);

// Print the command
void	print_command(t_cmd *cmd);

// Print all the commands
void	print_all_commands(t_shell *shell);

#endif