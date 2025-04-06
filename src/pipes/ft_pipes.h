#ifndef FT_PIPES_H
# define FT_PIPES_H

# include "../minishell.h"

// make ALL pipes
int		make_pipes(t_shell *shell);

// close ONE pipe
void	close_pipe(t_cmd *cmd);

// close ALL pipes
void	close_all_pipes(t_shell *shell);

// close the correct pipe
void	close_correct_pipe(t_cmd *cmd);

// handle the duplication of the file descriptors
void	dup_handles(t_cmd *cmd, t_shell *shell);

// process the pipe
void	process_pipe(t_cmd *cmd, t_shell *shell);

#endif