#ifndef REDIRECTIONS_H
# define REDIRECTIONS_H

# include "../minishell.h"

/*void	ft_redir_in(t_cmd *cmd, t_shell *shell);
void	ft_redir_out(t_cmd *cmd, t_shell *shell);
void	ft_redir_append(t_cmd *cmd, t_shell *shell);
void	ft_redir_heredoc(t_cmd *cmd, t_shell *shell);
void	cleanup_temp_files(t_cmd **cmds);*/
// void reset_redirections(t_cmd *cmd, t_shell *shell);
int handle_redirections(t_fd *fd_struct, t_shell *shell);
void manage_redirs(t_fd *fd_struct, t_shell *shell);
void close_cmd_redirs(t_cmd *cmd);
int assign_redirs(t_cmd *cmd, t_shell *shell);
int setup_redirections(t_cmd *cmd, t_shell *shell);

#endif