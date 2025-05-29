#ifndef FT_PIPES_H
# define FT_PIPES_H

// piping functions

# include "../minishell.h"

// function to create pipes for the commands
int		make_pipes(t_cmd *cmd, t_shell *shell);

// function to close pipes
void	close_pipes(t_cmd *cmd);

// function to close pipes after forking
void	close_pipes_after_fork(t_cmd *cmd);

// function to manage pipes
void	manage_pipes(t_cmd *cmd, t_shell *shell);

void	close_safe(int fd);

void	close_parent_redirections(t_cmd *cmd);

void	close_pipes(t_cmd *cmd);

void	close_pipe(t_cmd *cmd);

void	close_child_pipes(t_cmd *cmd);

#endif