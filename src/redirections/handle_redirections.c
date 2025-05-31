#include "redirections.h"

// function to handle redir out
static int	handle_redir_out(t_fd *redir, t_shell *shell)
{
	redir->fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (redir->fd == -1)
	{
		ft_printf_fd(STDERR_FILENO, "minishell: %s: " NOFILE "\n", redir->file);
		shell->exit_value = 1;
		return (1);
	}
	return (0);
}

// function to handle redir in
static int	handle_redir_in(t_fd *redir, t_shell *shell)
{
	redir->fd = open(redir->file, O_RDONLY);
	if (redir->fd == -1)
	{
		ft_printf_fd(STDERR_FILENO, "minishell: %s: " NOFILE "\n", redir->file);
		shell->exit_value = 1;
		return (1);
	}
	return (0);
}

// function to handle redir append
static int	handle_redir_append(t_fd *redir, t_shell *shell)
{
	redir->fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (redir->fd == -1)
	{
		ft_printf_fd(STDERR_FILENO, "minishell: %s: " NOFILE "\n", redir->file);
		shell->exit_value = 1;
		return (1);
	}
	return (0);
}

// function to handle heredoc redirection
static int	handle_heredoc(t_fd *redir, t_shell *shell)
{
	if (ft_handle_heredoc(redir, shell) == 130)
	{	
		setup_signals(shell);
		return (130);
	}
	redir->fd = open(HERE_DOC, O_RDONLY);
	if (redir->fd == -1)
	{
		ft_printf_fd(STDERR_FILENO, "minishell: %s: " NOFILE "\n", HERE_DOC);
		shell->exit_value = 1;
		return (1);
	}
	return (0);
}

// function to handle all types of redirections
int	handle_redirections(t_fd *fd_struct, t_shell *shell)
{
	t_fd	*tmp;

	tmp = fd_struct;
	if (!tmp)
		return (shell->exit_value = 1, 1);
	if (tmp->type == HERE_DOC_)
		return (handle_heredoc(tmp, shell));
	else if (tmp->type == REDIR_OUT)
		return (handle_redir_out(tmp, shell));
	else if (tmp->type == REDIR_IN)
		return (handle_redir_in(tmp, shell));
	else if (tmp->type == REDIR_APPEND)
		return (handle_redir_append(tmp, shell));
	else
	{
		shell->exit_value = 1;
		return (1);
	}
}
