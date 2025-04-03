#ifndef REDIRECTIONS_H
# define REDIRECTIONS_H

# include "../minishell.h"

void	ft_redir_in(t_cmd *cmd, t_shell *shell);
void	ft_redir_out(t_cmd *cmd, t_shell *shell);
void	ft_redir_append(t_cmd *cmd, t_shell *shell);
void	ft_redir_heredoc(t_cmd *cmd, t_shell *shell);
void	cleanup_temp_files(t_cmd **cmds);

#endif