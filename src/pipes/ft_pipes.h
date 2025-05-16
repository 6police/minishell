#ifndef FT_PIPES_H
# define FT_PIPES_H

// piping functions

# include "../minishell.h"

// function to create pipes for the commands
int make_pipes(t_cmd *cmd, t_shell *shell);

// function to close pipes
void close_pipes(t_cmd *cmd);

// function to manage pipes
void manage_pipes(t_cmd *cmd, t_shell *shell);


#endif