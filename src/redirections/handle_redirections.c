#include "redirections.h"


static int handle_redir_out(t_fd *redir, t_shell *shell)
{
	redir->fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (redir->fd == -1)
	{
		ft_printf_fd(STDERR_FILENO, "minishell: %s: No such file or directory\n", redir->file);
		shell->exit_value = 1;
		return (1);
	}
	return (0);
}

static int handle_redir_in(t_fd *redir, t_shell *shell)
{
	redir->fd = open(redir->file, O_RDONLY);
	if (redir->fd == -1)
	{
		ft_printf_fd(STDERR_FILENO, "minishell: %s: No such file or directory\n", redir->file);
		shell->exit_value = 1;
		return (1);
	}
	return (0);
}

static int handle_redir_append(t_fd *redir, t_shell *shell)
{
	redir->fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (redir->fd == -1)
	{
		ft_printf_fd(STDERR_FILENO, "minishell: %s: No such file or directory\n", redir->file);
		shell->exit_value = 1;
		return (1);
	}
	return (0);
}

static int handle_heredoc(t_fd *redir, t_shell *shell)
{
	ft_handle_heredoc(redir, shell);
	redir->fd = open(HERE_DOC, O_RDONLY);
	if (redir->fd == -1)
	{
		ft_printf_fd(STDERR_FILENO, "minishell: %s: No such file or directory\n", redir->file);
		shell->exit_value = 1;
		return (1);
	}
	return (0);
}

int handle_redirections(t_fd *fd_struct, t_shell *shell)
{
	t_fd *tmp;

	tmp = fd_struct;

	if (!tmp)
		return (shell->exit_value = 1, 1);
	
	if (tmp->type == HERE_DOC_)
		return(handle_heredoc(tmp, shell));

	else if (tmp->type == REDIR_OUT)
		return(handle_redir_out(tmp, shell));
	else if (tmp->type == REDIR_IN)
		return(handle_redir_in(tmp, shell));
	else if (tmp->type == REDIR_APPEND)
		return(handle_redir_append(tmp, shell));
	else
	{
		shell->exit_value = 1;
		return (1);
	}
}
// function to close all the redirections in a single command
void close_cmd_redirs(t_cmd *cmd)
{
	if (!cmd->fd_struct)
		return;
		
	t_fd *tmp;

	tmp = cmd->fd_struct;
	if (!tmp)
		return;
	while (tmp)
	{
		if (tmp->fd != -1)
		{
			close(tmp->fd);
			tmp->fd = -1;
		}
		if (tmp->type == HERE_DOC_)
		{
			unlink(HERE_DOC);
			free(tmp->file);
			tmp->file = NULL;
		}
		tmp = tmp->next;
	}
}
// function to set up the redirections for a command
int setup_redirections(t_cmd *cmd, t_shell *shell)
{
	if (!cmd || !cmd->fd_struct)
		return (0);

	t_fd *tmp = cmd->fd_struct;
	t_fd *last_in = NULL;
	t_fd *last_out = NULL;

	// First, open all
	while (tmp)
	{
		if (handle_redirections(tmp, shell) == 1)
			return (1); // open failed
		if (tmp->type == REDIR_IN || tmp->type == HERE_DOC_)
			last_in = tmp;
		else if (tmp->type == REDIR_OUT || tmp->type == REDIR_APPEND)
			last_out = tmp;
		tmp = tmp->next;
	}

	// Second, dup2 only last input/output
	if (last_in && last_in->fd != -1)
	{
		if (dup2(last_in->fd, STDIN_FILENO) == -1)
		{
			perror("dup2 input");
			shell->exit_value = 1;
			return (1);
		}
	}

	if (last_out && last_out->fd != -1)
	{
		if (dup2(last_out->fd, STDOUT_FILENO) == -1)
		{
			perror("dup2 output");
			shell->exit_value = 1;
			return (1);
		}
	}

	// Finally, close everything (but NOT STDIN/OUT)
	tmp = cmd->fd_struct;
	while (tmp)
	{
		if (tmp->fd != -1)
		{
			close(tmp->fd);
			tmp->fd = -1;
			if (tmp->type == HERE_DOC_)
			{
				unlink(HERE_DOC);
				free(tmp->file);
				tmp->file = NULL;
			}
		}
		tmp = tmp->next;
	}
	return (0);
}

