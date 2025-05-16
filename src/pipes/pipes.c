#include "ft_pipes.h"

// function to create pipes for the commands
int	make_pipes(t_cmd *cmd, t_shell *shell)
{
	if (!cmd || shell->is_pipe == false)
		return (0);
	
	t_cmd	*tmp;
	
	tmp = cmd;
	while (tmp->next)
	{
		if (pipe(tmp->fd) == -1)
		{
			shell->exit_value = 1;
			return (1);
		}
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
		close(cmd->fd[0]);
	}
	// if (!cmd->next)
		// close (cmd->fd[0] );
}



// if (cmd_index == 0)
// 	{
// 		close(pipex->cmds[cmd_index]->fd[0]);
// 		dup2(pipex->infile, STDIN_FILENO);
// 		close(pipex->infile);
// 		dup2(pipex->cmds[cmd_index]->fd[1], STDOUT_FILENO);
// 		close(pipex->cmds[cmd_index]->fd[1]);
// 	}
// 	else if (cmd_index == pipex->n_cmds - 1)
// 	{
// 		close(pipex->cmds[cmd_index - 1]->fd[1]);
// 		dup2(pipex->outfile, STDOUT_FILENO);
// 		close(pipex->outfile);
// 		dup2(pipex->cmds[cmd_index - 1]->fd[0], STDIN_FILENO);
// 		close(pipex->cmds[cmd_index - 1]->fd[0]);
// 	}
// 	else
// 	{
// 		close(pipex->cmds[cmd_index - 1]->fd[1]);
// 		close(pipex->cmds[cmd_index]->fd[0]);
// 		dup2(pipex->cmds[cmd_index - 1]->fd[0], STDIN_FILENO);
// 		close(pipex->cmds[cmd_index - 1]->fd[0]);
// 		dup2(pipex->cmds[cmd_index]->fd[1], STDOUT_FILENO);
// 		close(pipex->cmds[cmd_index]->fd[1]);
// 	}
// }