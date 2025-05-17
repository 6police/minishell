#include "ft_run.h"

void	pipe_builtin(t_cmd *cmd, t_shell *shell)
{
	if (!shell->is_pipe)
	{
		if (!cmd->is_builtin)
		{
			cmd->pid = fork();
			if (cmd->pid == -1)
			{
				ft_putstr_fd("minishell: fork failed\n", STDERR_FILENO);
				shell->exit_value = 1;
				return ;
			}
			if (cmd->pid == 0)
			{
				shell->is_child = true;
				signal(SIGQUIT, SIG_DFL);
				signal(SIGINT, SIG_DFL);
				if (setup_redirections(cmd, shell) == 1)
					clean_exit(&shell);
				execute_external(cmd, shell);
				clean_exit(&shell);
			}
			else
			{
				waitpid(cmd->pid, NULL, 0);
				shell->is_child = false;
			}
		}
		else
		{
			shell->is_child = true;
			signal(SIGQUIT, SIG_DFL);
			signal(SIGINT, SIG_DFL);
			// Builtin execution
			if (setup_redirections(cmd, shell) == 1)
				clean_exit(&shell);
			cmd->builtin_func(cmd, shell);
			clean_exit(&shell);
		}
		return ;
	}
	// In case of pipe, we need to fork and execute the command
	cmd->pid = fork();
	if (cmd->pid == -1)
	{
		ft_putstr_fd("minishell: fork failed\n", STDERR_FILENO);
		shell->exit_value = 1;
		return ;
	}
	if (cmd->pid == 0)
	{
		shell->is_child = true;
		if (setup_redirections(cmd, shell) == 1)
			clean_exit(&shell);
		manage_pipes(cmd, shell);
		// Builtin execution
		cmd->builtin_func(cmd, shell);
		clean_exit(&shell);
	}
	// In parent process, after forking
	else
	{
		close_pipes(shell->cmds);
	}
}

void	run_commands(t_shell *shell)
{
	t_cmd *tmp;

	if (!shell->cmds)
		return ;

	tmp = shell->cmds;

	// Setup pipes
	tmp = shell->cmds;
	
	if (shell->is_pipe)
		if (make_pipes(tmp, shell) == 1)
			return ;
	
	if (setup_redirections(tmp, shell) == 1)
	{
		clean_exit(&shell);
		return ;
	}
	


	// Launch commands
	tmp = shell->cmds;
	while (tmp)
	{
		if (tmp->is_valid)
			pipe_builtin(tmp, shell);
		else
		{
			ft_printf_fd(STDERR_FILENO, "%s: command not found\n",
				tmp->args[0]);
			shell->exit_value = 127;
		}
		tmp = tmp->next;
	}
	// Wait for all children
	tmp = shell->cmds;
	while (tmp)
	{
		if (tmp->pid > 0)
			waitpid(tmp->pid, NULL, 0);
		tmp = tmp->next;
	}
	// // Close pipes
	close_pipes(shell->cmds);
}