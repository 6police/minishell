#include "redirections.h"

// function to close the specific pipes
static void	close_specific_pipe(t_cmd *cmd)
{
	if (cmd->prev)
	{
		close_safe(cmd->prev->fd_pipe[0]);
		close_safe(cmd->prev->fd_pipe[1]);
	}
}

// function to close all the redirections in a single command
void	close_cmd_redirs(t_cmd *cmd)
{
	t_fd	*tmp;


	if (!cmd->fd_struct)
		return ;
	tmp = cmd->fd_struct;
	if (!tmp)
		return ;
	
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
	close_specific_pipe(cmd);
}

// function to set up the redirections for a command
int	setup_redirections(t_cmd *cmd, t_shell *shell)
{
	t_fd	*tmp;
	t_fd	*last_in;
	t_fd	*last_out;
	int		i;

	if (!cmd || !cmd->fd_struct)
		return (0);
	tmp = cmd->fd_struct;
	last_in = NULL;
	last_out = NULL;
	while (tmp)
	{
		i = handle_redirections(tmp, shell);
		if (i == 1 || i == 130)
			return (i);
		if (tmp->type == REDIR_IN || tmp->type == HERE_DOC_)
			last_in = tmp;
		else if (tmp->type == REDIR_OUT || tmp->type == REDIR_APPEND)
			last_out = tmp;
		tmp = tmp->next;
	}
	if (last_in && last_in->fd != -1)
		cmd->fd[0] = last_in->fd;
	if (last_out && last_out->fd != -1)
		cmd->fd[1] = last_out->fd;
	return (0);
}
