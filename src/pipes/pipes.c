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

// void	close_pipes(t_cmd *cmd)
// {
// 	t_cmd	*tmp;

// 	if (!cmd || !cmd->next)
// 		return ;
// 	tmp = cmd;
// 	while (tmp && tmp->next)
// 	{
// 		close(tmp->fd_pipe[0]);
// 		close(tmp->fd_pipe[1]);
// 		tmp = tmp->next;
// 	}
// }

// function to manage pipes
// void	manage_pipes(t_cmd *cmd, t_shell *shell)
// {
// 	t_cmd	*tmp;

// 	if (!cmd || shell->is_pipe == false)
// 		return ;

// 	tmp = cmd;
// 	// If there's input from previous pipe
// 	if (cmd->prev)
// 		dup2(cmd->prev->fd_pipe[0], STDIN_FILENO);
// 	// If there's output to next pipe
// 	if (cmd->next)
// 		dup2(cmd->fd_pipe[1], STDOUT_FILENO);
// 	// Now close ALL pipe fd_pipes in the current cmd
// 	if (cmd->prev)
// 	{
// 		close(cmd->prev->fd_pipe[0]);
// 		close(cmd->prev->fd_pipe[1]);
// 	}
// 	if (cmd->next)
// 	{
// 		close(cmd->fd_pipe[0]);
// 		close(cmd->fd_pipe[1]);
// 	}
// 	// if (!cmd->next)
// 	// close (cmd->fd_pipe[0] );
// }
void	manage_pipes(t_cmd *cmd, t_shell *shell)
{
	t_cmd	*tmp;

	if (!cmd || shell->is_pipe == false)
		return ;

	// INPUT: redir input has priority, else pipe input from prev
	if (cmd->fd[0] != -1)
	{
		dup2(cmd->fd[0], STDIN_FILENO);
		close(cmd->fd[0]);
		cmd->fd[0] = -1;
	}
	else if (cmd->prev && cmd->prev->fd_pipe[0] != -1)
	{
		dup2(cmd->prev->fd_pipe[0], STDIN_FILENO);
		close(cmd->prev->fd_pipe[0]);
		cmd->prev->fd_pipe[0] = -1;
	}
	
	// OUTPUT: redir output has priority, else pipe output to next
	if (cmd->fd[1] != -1)
	{
		dup2(cmd->fd[1], STDOUT_FILENO);
		close(cmd->fd[1]);
		cmd->fd[1] = -1;
	}
	else if (cmd->next && cmd->fd_pipe[1] != -1)
	{
		dup2(cmd->fd_pipe[1], STDOUT_FILENO);
		close(cmd->fd_pipe[1]);
		cmd->fd_pipe[1] = -1;
	}


	// Close all pipe fds inherited from parent
	
	tmp = shell->cmds;
	while (tmp)
	{
		if (tmp != cmd->prev && tmp->fd_pipe[0] != -1)
		{
			close(tmp->fd_pipe[0]);
			tmp->fd_pipe[0] = -1;
		}
		if (tmp != cmd && tmp->fd_pipe[1] != -1)
		{
			close(tmp->fd_pipe[1]);
			tmp->fd_pipe[1] = -1;
		}
		tmp = tmp->next;
	}
}

// if (cmd_index == 0)
// 	{
// 		close(pipex->cmds[cmd_index]->fd_pipe[0]);
// 		dup2(pipex->infile, STDIN_FILENO);
// 		close(pipex->infile);
// 		dup2(pipex->cmds[cmd_index]->fd_pipe[1], STDOUT_FILENO);
// 		close(pipex->cmds[cmd_index]->fd_pipe[1]);
// 	}
// 	else if (cmd_index == pipex->n_cmds - 1)
// 	{
// 		close(pipex->cmds[cmd_index - 1]->fd_pipe[1]);
// 		dup2(pipex->outfile, STDOUT_FILENO);
// 		close(pipex->outfile);
// 		dup2(pipex->cmds[cmd_index - 1]->fd_pipe[0], STDIN_FILENO);
// 		close(pipex->cmds[cmd_index - 1]->fd_pipe[0]);
// 	}
// 	else
// 	{
// 		close(pipex->cmds[cmd_index - 1]->fd_pipe[1]);
// 		close(pipex->cmds[cmd_index]->fd_pipe[0]);
// 		dup2(pipex->cmds[cmd_index - 1]->fd_pipe[0], STDIN_FILENO);
// 		close(pipex->cmds[cmd_index - 1]->fd_pipe[0]);
// 		dup2(pipex->cmds[cmd_index]->fd_pipe[1], STDOUT_FILENO);
// 		close(pipex->cmds[cmd_index]->fd_pipe[1]);
// 	}
// }