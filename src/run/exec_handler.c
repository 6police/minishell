#include "ft_run.h"

void eggxecutor (t_cmd *cmd, t_shell *shell)
{
	shell->is_child = true;
	if (setup_redirections(cmd, shell) == 1)
		clean_exit(&shell);
}

void run_pipe(t_cmd *cmd, t_shell *shell)
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
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, SIG_DFL);
		eggxecutor(cmd, shell);
		manage_pipes(cmd, shell);
		close_pipes(shell->cmds);
		cmd->builtin_func(cmd, shell);
		clean_exit(&shell);
	}
	else
		close_pipes_after_fork(cmd);
}

void run_no_pipe(t_cmd *cmd, t_shell *shell)
{
	if (!cmd || !shell || shell->is_pipe)
		return ;
	if (!cmd->is_builtin)
	{
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
			signal(SIGQUIT, SIG_DFL);
			signal(SIGINT, SIG_DFL);
			eggxecutor(cmd, shell);
			cmd->builtin_func(cmd, shell);
			clean_exit(&shell);
		}
	}
	else
	{
		shell->is_child = true;
		shell->wait = false;
		eggxecutor(cmd, shell);
		shell->is_child = false;
		cmd->builtin_func(cmd, shell);
	}
}

void processor(t_cmd *cmd, t_shell *shell)
{
	if (!cmd || !shell)
		return ;

	if (shell->is_pipe)
		run_pipe(cmd, shell);
	else
		run_no_pipe(cmd, shell);
}
