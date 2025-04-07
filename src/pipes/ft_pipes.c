#include "ft_pipes.h"

// make ALL pipes

int	make_pipes(t_shell *shell)
{
	t_cmd	*cmd;

	if (!shell->is_pipe)
		return (0);
	cmd = shell->cmds;
	if (!cmd)
		return (0);
	while (cmd->next)
	{
		if (pipe(cmd->fd) == -1)
			return (ft_printf_fd(2, "Error: pipe failed\n"));
		cmd = cmd->next;
	}
	return (0);
}

// close ONE pipe
void	close_pipe(t_cmd *cmd)
{
	close(cmd->fd[0]);
	close(cmd->fd[1]);
}

// close ALL pipes
void	close_all_pipes(t_shell *shell)
{
	t_cmd	*cmd;

	if (!shell->is_pipe)
		return ;
	cmd = shell->cmds;
	while (cmd)
	{
		close_pipe(cmd);
		cmd = cmd->next;
	}
}

// close the correct pipe
void	close_correct_pipe(t_cmd *cmd)
{
	if (!cmd)
		return ;
	if (!cmd->prev)
		close(cmd->fd[1]);
	else if (!cmd->next)
		close(cmd->prev->fd[0]);
	else
		close_pipe(cmd);
}

// dup handles
void	dup_handles(t_cmd *cmd, t_shell *shell)
{
	if ((!shell->is_pipe) || !cmd)
		return ;
	(void)shell;
	if (cmd->prev == NULL)
	{
		close(cmd->fd[0]);
		// dup2(shell->infile, STDIN_FILENO);
		// close(shell->infile);
		dup2(cmd->fd[1], STDOUT_FILENO);
		// close(cmd->fd[1]);
	}
	else if (cmd->next == NULL)
	{
		close(cmd->prev->fd[1]);
		// dup2(shell->outfile, STDOUT_FILENO);
		// close(shell->outfile);
		dup2(cmd->prev->fd[0], STDIN_FILENO);
		// close(cmd->prev->fd[0]);
	}
	else
	{
		close(cmd->prev->fd[1]);
		close(cmd->fd[0]);
		dup2(cmd->prev->fd[0], STDIN_FILENO);
		close(cmd->prev->fd[0]);
		dup2(cmd->fd[1], STDOUT_FILENO);
		close(cmd->fd[1]);
	}
}

// fork the process
void	process_pipe(t_cmd *cmd, t_shell *shell)
{
	dup_handles(cmd, shell);
	close_all_pipes(shell);
	//	close(shell->infile);
	//	close(shell->outfile);
	// execute command!!!!
}

// int	process_command(t_cmd *cmd, t_shell *shell)
// {
// 	dup_handles(cmd, shell);
// 	close_pipes(pipex);
// 	close(pipex->infile);
// 	close(pipex->outfile);
// 	if (pipex->cmds[cmd_index]->path == NULL)
// 	{
// 		ft_printf_fd(2, "Error: command not found: %s\n",
// 			pipex->cmds[cmd_index]->cmd);
// 		clean_house(pipex);
// 		return (1);
// 	}
// 	(execve(pipex->cmds[cmd_index]->path, pipex->cmds[cmd_index]->args,
// 			pipex->envp));
// 	return (0);
// }

// static void	close_piperino(t_pipe *pipex, int cmd_index)
// {
// 	if (cmd_index > 0)
// 		close(pipex->cmds[cmd_index - 1]->fd[0]);
// 	if (cmd_index < pipex->n_cmds - 1)
// 		close(pipex->cmds[cmd_index]->fd[1]);
// }

// void	wait_for_children(t_pipe *pipex)
// {
// 	int	i;

// 	i = 0;
// 	while (i < pipex->n_cmds)
// 	{
// 		waitpid(pipex->cmds[i]->pid, &pipex->cmds[i]->status, 0);
// 		i++;
// 	}
// }

// void	forking(t_pipe *pipex)
// {
// 	int i;

// 	i = 0;
// 	if (!pipex->cmds)
// 		exit_error(pipex, "Error: no commands found");
// 	while (i < pipex->n_cmds)
// 	{
// 		pipex->cmds[i]->pid = fork();
// 		if (pipex->cmds[i]->pid == 0)
// 		{
// 			if (process_command(pipex, i) != 0)
// 				exit(1);
// 		}
// 		else if (pipex->cmds[i]->pid < 0)
// 		{
// 			ft_printf_fd(2, "Error: fork failed\n");
// 			exit(1);
// 		}
// 		else
// 			close_piperino(pipex, i);
// 		i++;
// 	}
// }