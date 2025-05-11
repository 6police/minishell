#include "ft_pipes.h"

// function to create pipes for the commands
int	make_pipes(t_cmd *cmd, t_shell *shell)
{
	if (!cmd || shell->is_pipe == false)
		return (0);
	
	t_cmd	*tmp;
	
	tmp = cmd;
	printf("Creating pipes... %p \n", cmd->prev);
	while (tmp->next)
	{
		if (pipe(tmp->fd) == -1)
		{
			ft_printf_fd(STDERR_FILENO, "Error: pipe failed\n");
			shell->exit_value = 1;
			return (1);
		}
		//ft_printf_fd(2, "READ: %d\n", tmp->fd[0]);
		//ft_printf_fd(2, "WRITE: %d\n", tmp->fd[1]);
		tmp = tmp->next;
	}
	return (0);
}

// close pipes
void	close_pipes(t_cmd *cmd)
{
	t_cmd	*tmp;

	if (!cmd || !cmd->next)
		return ;
	tmp = cmd;
	while (tmp && tmp->next)
	{
		close(tmp->fd[0]);
		close(tmp->fd[1]);
		tmp = tmp->next;
	}
}

// function to manage pipes
void	manage_pipes(t_cmd *cmd, t_shell *shell)
{
	if (!cmd || shell->is_pipe == false)
		return ;

	t_cmd	*tmp;
	tmp = cmd;


	if (cmd->prev)
	{
		dup2(cmd->prev->fd[0], STDIN_FILENO);
		close(cmd->prev->fd[0]);
		close(cmd->prev->fd[1]);
	}
	if (cmd->next)
	{
		dup2(cmd->fd[1], STDOUT_FILENO);
		close(cmd->fd[1]);
	}
	if (!cmd->next)
		close (cmd->fd[0]);
}
