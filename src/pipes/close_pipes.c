#include "ft_pipes.h"

// close pipes safely
void	close_safe(int fd)
{
	if (fd != -1)
		close(fd);
}
// function to close pipes after forking (parent closes unused ends)
void	close_pipes_after_fork(t_cmd *cmd)
{
	// Parent closes the pipe ends it doesn't need
	// The child will inherit copies before we close them
	if (cmd->prev && cmd->prev->fd_pipe[0] != -1)
	{
		close_safe(cmd->prev->fd_pipe[0]);
			// Parent done reading from previous pipe
		cmd->prev->fd_pipe[0] = -1;
	}
	if (cmd->next && cmd->fd_pipe[1] != -1)
	{
		close_safe(cmd->fd_pipe[1]); // Parent done writing to current pipe
		cmd->fd_pipe[1] = -1;
	}
}

// New function to close redirection FDs in parent after fork
void	close_parent_redirections(t_cmd *cmd)
{
	t_fd	*tmp;

	if (!cmd || !cmd->fd_struct)
		return ;
	tmp = cmd->fd_struct;
	while (tmp)
	{
		if (tmp->fd != -1)
		{
			close_safe(tmp->fd);
			tmp->fd = -1;
		}
		tmp = tmp->next;
	}
}

// function to close all pipes in the command list (cleanup)
void	close_pipes(t_cmd *cmd)
{
	t_cmd	*tmp;

	tmp = cmd;
	while (tmp)
	{
		if (tmp->fd_pipe[0] != -1)
		{
			close_safe(tmp->fd_pipe[0]);
			tmp->fd_pipe[0] = -1;
		}
		if (tmp->fd_pipe[1] != -1)
		{
			close_safe(tmp->fd_pipe[1]);
			tmp->fd_pipe[1] = -1;
		}
		tmp = tmp->next;
	}
}

// function to close the pipe file descriptors in a command
void	close_pipe(t_cmd *cmd)
{
	if (cmd->fd_pipe[0] != -1)
	{
		close_safe(cmd->fd_pipe[0]);
		cmd->fd_pipe[0] = -1;
	}
	if (cmd->fd_pipe[1] != -1)
	{
		close_safe(cmd->fd_pipe[1]);
		cmd->fd_pipe[1] = -1;
	}
}

// Close pipe ends in child process after dup2
void	close_child_pipes(t_cmd *cmd)
{
	// Close all pipe ends after duplicating them in child
	if (cmd->prev)
	{
		if (cmd->prev->fd_pipe[0] > 2)
		{
			close_safe(cmd->prev->fd_pipe[0]);
			cmd->prev->fd_pipe[0] = -1;
		}
		if (cmd->prev->fd_pipe[1] > 2)
		{
			close_safe(cmd->prev->fd_pipe[1]);
			cmd->prev->fd_pipe[1] = -1;
		}
	}
	if (cmd->fd_pipe[0] > 2)
	{
		close_safe(cmd->fd_pipe[0]);
		cmd->fd_pipe[0] = -1;
	}
	if (cmd->fd_pipe[1] > 2)
	{
		close_safe(cmd->fd_pipe[1]);
		cmd->fd_pipe[1] = -1;
	}
}

void close_parent_pipes(t_cmd *cmd)
{
	// Close all pipe ends in parent after forking
	if (cmd->prev)
	{
		close_safe(cmd->prev->fd_pipe[0]);
		cmd->prev->fd_pipe[0] = -1;
	}
	if (cmd)
	{
		close_safe(cmd->fd_pipe[1]);
		cmd->fd_pipe[1] = -1;
	}
}