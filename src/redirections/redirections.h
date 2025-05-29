#ifndef REDIRECTIONS_H
# define REDIRECTIONS_H

# include "../minishell.h"

// Function prototypes for redirection handling in a shell

int		handle_redirections(t_fd *fd_struct, t_shell *shell);
void	manage_redirs(t_fd *fd_struct, t_shell *shell);
void	close_cmd_redirs(t_cmd *cmd);
int		assign_redirs(t_cmd *cmd, t_shell *shell);
int		setup_redirections(t_cmd *cmd, t_shell *shell);
int	ft_handle_heredoc(t_fd *fd_struct, t_shell *shell);
bool	has_expansion(char *line);
char	*ft_expand(char *line, t_shell *shell);

#endif