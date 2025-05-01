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

// static void handle_heredoc(t_fd *redir, t_shell *shell)
// {
// 	**** HANDLE HERE DOC ****
// }

int handle_redirections(t_fd *fd_struct, t_shell *shell)
{
	t_fd *tmp;

	tmp = fd_struct;

	if (!tmp)
		return (shell->exit_value = 1, 1);
	// if (tmp->type == HERE_DOC_)
	// 	handle_heredoc(tmp, shell);

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

// function to open and manage all the redirections in a single command
void manage_redirs(t_fd *fd_struct, t_shell *shell)
{
	if (!fd_struct)
		return;

	t_fd *tmp;
	int last_in;
	int last_out;

	tmp = fd_struct;
	if (!tmp)
		return;
	last_in = -1;
	last_out = -1;

	while (tmp)
	{
		if (handle_redirections(tmp, shell) == 1)
			return;
			
		//close previous same type redirections if any
		if (tmp->type == REDIR_IN && last_in != -1)
		{
			close(last_in);
			last_in = -1;
		}
		else if (tmp->type == REDIR_OUT && last_out != -1)
		{
			close(last_out);
			last_out = -1;
		}

		// open the new redirection
		
		//store the current as last fd of this type
		if (tmp->type == REDIR_IN)
			last_in = tmp->fd;
		else if (tmp->type == REDIR_OUT || tmp->type == REDIR_APPEND)
			last_out = tmp->fd;
		tmp = tmp->next;
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
		tmp = tmp->next;
	}
}

int assign_redirs(t_cmd *cmd, t_shell *shell)
{
	if (!cmd->fd_struct)
		return 1;
		
	t_fd *tmp;
	t_fd *last_in;
	t_fd *last_out;

	tmp = cmd->fd_struct;
	last_in = NULL;
	last_out = NULL;

	// set the lasat input and output redirections
	while (tmp)
	{
		if (tmp->type == REDIR_IN)
			last_in = tmp;
		else if (tmp->type == REDIR_OUT || tmp->type == REDIR_APPEND)
			last_out = tmp;
		tmp = tmp->next;
	}

	// re-loop and close unused redirections
	tmp = cmd->fd_struct;
	while (tmp)
	{
		if (tmp->type == REDIR_IN && tmp != last_in)
		{
			close(tmp->fd);
			tmp->fd = -1;
		}
		else if ((tmp->type == REDIR_OUT || tmp->type == REDIR_APPEND) && tmp != last_out)
		{
			close(tmp->fd);
			tmp->fd = -1;
		}
		tmp = tmp->next;
	}

	// apply dup2 to the last input and output redirections
	if (last_in)
	{
		if (last_in->fd == -1)
		{
			ft_printf_fd(STDERR_FILENO, "minishell: %s: No such file or directory \n", last_in->file);
			shell->exit_value = 1;
			return (1);
		}
		if (dup2(last_in->fd, STDIN_FILENO) == -1)
		{
			ft_printf_fd(STDERR_FILENO, "minishell: dup2 input %s \n", last_in->file);
			shell->exit_value = 1;
			return (1);
		}
		close(last_in->fd);
	}

	if (last_out)
	{
		if (last_out->fd == -1)
		{
			ft_printf_fd(STDERR_FILENO, "minishell: %s: No such file or directory \n", last_out->file);
			shell->exit_value = 1;
			return (1);
		}
		if (dup2(last_out->fd, STDOUT_FILENO) == -1)
		{
			ft_printf_fd(STDERR_FILENO, "minishell: dup2 output %s \n", last_out->file);
			shell->exit_value = 1;
			return (1);
		}
		close(last_out->fd);
	}
	return (0);
}