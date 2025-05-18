#include "ft_pipes.h"

// function to create pipes for the commands
int	make_pipes(t_cmd *cmd, t_shell *shell)
{
	t_cmd	*tmp;

	if (!cmd || shell->is_pipe == false)
		return (0);
	tmp = cmd;
	while (tmp->next)
	{
		if (pipe(tmp->fd_pipe) == -1)
		{
			ft_printf_fd(STDERR_FILENO, "minishell: pipe failed\n");
			shell->exit_value = 1;
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

// close pipes
static void	close_safe(int fd)
{
	if (fd != -1)
		close(fd);
}
void	close_pipes(t_cmd *cmd)
{
	t_cmd	*tmp;

	tmp = cmd;
	while (tmp)
	{
		close_safe(tmp->fd_pipe[0]);
		close_safe(tmp->fd_pipe[1]);
		tmp = tmp->next;
	}
}

void manage_pipes(t_cmd *cmd, t_shell *shell)
{
	if (!cmd || !shell->is_pipe)
		return;

	// If input redirection is set, use it
	if (cmd->fd[0] != -1)
		dup2(cmd->fd[0], STDIN_FILENO);
	else if (cmd->prev)
		dup2(cmd->prev->fd_pipe[0], STDIN_FILENO);

	// If output redirection is set, use it
	if (cmd->fd[1] != -1)
		dup2(cmd->fd[1], STDOUT_FILENO);
	else if (cmd->next)
		dup2(cmd->fd_pipe[1], STDOUT_FILENO);
}

void close_pipes_after_fork(t_cmd *cmd)
{
	if (cmd->prev)
		close_safe(cmd->prev->fd_pipe[0]);
	if (cmd->next)
		close_safe(cmd->fd_pipe[1]);
}

