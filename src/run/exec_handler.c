#include "ft_run.h"


// function to close file des in a command
void	close_fds(t_cmd *cmd)
{
	t_fd *tmp;

	if (!cmd || !cmd->fd_struct)
		return ;

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
}

// wrapper to handle fd duplication and signal handling
void	eggxecutor(t_cmd *cmd, t_shell *shell, int flag)
{
	if (flag == 1)
	{
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, SIG_DFL);
		shell->is_child = true;
		if (cmd->fd[0] != -1)
			dup2(cmd->fd[0], STDIN_FILENO);
		if (cmd->fd[1] != -1)
			dup2(cmd->fd[1], STDOUT_FILENO);
		close_fds(cmd);
	}
	(void)cmd;
}

// function to run a command with pipes
void	run_pipe(t_cmd *cmd, t_shell *shell)
{
	if (!cmd || !shell || !shell->is_pipe)
		return ;
	shell->wait = true;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
	cmd->pid = fork();
	if (cmd->pid == -1)
	{
		ft_putstr_fd("minishell: fork failed\n", STDERR_FILENO);
		shell->exit_value = 1;
		return ;
	}
	if (cmd->pid == 0)
	{
		manage_pipes(cmd, shell);
		eggxecutor(cmd, shell, 1);
		close_pipes(shell->cmds);
		cmd->builtin_func(cmd, shell);
		close_fds(cmd);
		clean_exit(&shell);
	}
	else
		close_pipes_after_fork(cmd);
}

// function to run a command without pipes
void	run_no_pipe(t_cmd *cmd, t_shell *shell)
{
	if (!cmd || !shell || shell->is_pipe)
		return ;
	if (!cmd->is_builtin)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, SIG_IGN);
		shell->wait = true;
		if (cmd->is_valid == false)
			return (ft_printf_fd(STDERR_FILENO, "%s command: not found\n", cmd->name),
				shell->exit_value = 127, (void)0);
		cmd->pid = fork();
		if (cmd->pid == -1)
		{
			ft_putstr_fd("minishell: fork failed\n", STDERR_FILENO);
			return (shell->exit_value = 1, (void)0);
		}
		if (cmd->pid == 0)
		{
			eggxecutor(cmd, shell, 1);
			cmd->builtin_func(cmd, shell);
			clean_exit(&shell);
		}
	}
	else
	{
		shell->wait = false;
		eggxecutor(cmd, shell, 0);
		shell->is_child = false;
		cmd->builtin_func(cmd, shell);
	}
}

// wrapper function to process a command
void	processor(t_cmd *cmd, t_shell *shell)
{
	if (!cmd || !shell)
		return ;
	if (shell->is_pipe)
		run_pipe(cmd, shell);
	else
		run_no_pipe(cmd, shell);
}
