#include "ft_pipes.h"

// function to create pipes for the commands
int make_pipes(t_cmd *cmd, t_shell *shell)
{
    if (!cmd || !cmd->next || shell->is_pipe == false)
        return (0);
    
    t_cmd *tmp;

    tmp = cmd;

    while (tmp && tmp->next)
    {
        if (pipe(tmp->fd) == -1)
        {
            ft_printf_fd(STDERR_FILENO, "Error: pipe failed\n");
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
    if (!cmd || !cmd->next)
        return;

    t_cmd *tmp1;
    t_cmd *tmp2;

    tmp1 = cmd;
    tmp2 = cmd->next;
    while (tmp2)
    {
        if (tmp1->fd[0] != -1)
            close(tmp1->fd[0]);
        if (tmp1->fd[1] != -1)
            close(tmp1->fd[1]);
        tmp1 = tmp2;
        tmp2 = tmp2->next;
    }
}

// function to manage pipes
void manage_pipes(t_cmd *cmd, t_shell *shell)
{
    if (!cmd || !cmd->next || shell->is_pipe == false)
        return;

    t_cmd *tmp;

    tmp = cmd;
	if (cmd->prev)  // if there's a previous command, read from it
		dup2(cmd->prev->fd[0], STDIN_FILENO);
	if (cmd->next)  // if there's a next command, write to it
		dup2(cmd->fd[1], STDOUT_FILENO);
}


/*




// close the correct pipe
void	close_correct_pipe(t_pipe *pipex, int cmd_index)
{
	if (cmd_index == 0)
		close(pipex->cmds[cmd_index]->fd[1]);
	else if (cmd_index == pipex->n_cmds - 1)
		close(pipex->cmds[cmd_index - 1]->fd[0]);
	else
		close_pipe(pipex, cmd_index);
}

void	dup_handles(t_pipe *pipex, int cmd_index)
{
	if (cmd_index == 0)
	{
		close(pipex->cmds[cmd_index]->fd[0]);
		dup2(pipex->infile, STDIN_FILENO);
		close(pipex->infile);
		dup2(pipex->cmds[cmd_index]->fd[1], STDOUT_FILENO);
		close(pipex->cmds[cmd_index]->fd[1]);
	}
	else if (cmd_index == pipex->n_cmds - 1)
	{
		close(pipex->cmds[cmd_index - 1]->fd[1]);
		dup2(pipex->outfile, STDOUT_FILENO);
		close(pipex->outfile);
		dup2(pipex->cmds[cmd_index - 1]->fd[0], STDIN_FILENO);
		close(pipex->cmds[cmd_index - 1]->fd[0]);
	}
	else
	{
		close(pipex->cmds[cmd_index - 1]->fd[1]);
		close(pipex->cmds[cmd_index]->fd[0]);
		dup2(pipex->cmds[cmd_index - 1]->fd[0], STDIN_FILENO);
		close(pipex->cmds[cmd_index - 1]->fd[0]);
		dup2(pipex->cmds[cmd_index]->fd[1], STDOUT_FILENO);
		close(pipex->cmds[cmd_index]->fd[1]);
	}
}







*/