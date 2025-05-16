#include "ft_run.h"

void	pipe_builtin(t_cmd *cmd, t_shell *shell)
{
	if (!shell->is_pipe)
	{
		cmd->builtin_func(cmd, shell);
		return ;
	}
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

		

		manage_pipes(cmd, shell);
		//close_pipes(cmd);
		
		// Builtin execution
		cmd->builtin_func(cmd, shell);
		clean_exit(&shell);
	}
	// In parent process, after forking
	else
	{
		if (cmd->prev )
		{
			close(cmd->prev->fd[0]);
		}
		if (cmd->next)
		{
			close(cmd->fd[1]);
		}
	}
}


void	run_commands(t_shell *shell)
{
	t_cmd	*tmp;

	if (!shell->cmds)
		return ;
	

	
	// Setup pipes
	tmp = shell->cmds;
	if (shell->is_pipe)
		if (make_pipes(tmp, shell) == 1)
			return ;

	while (tmp)
	{
		setup_redirections(tmp, shell);
		tmp = tmp->next;
	}
	// Launch commands
	tmp = shell->cmds;
	while (tmp)
	{
		if (tmp->is_valid)
			pipe_builtin(tmp, shell);
		else
		{
			ft_printf_fd(STDERR_FILENO, "%s: command not found\n", tmp->args[0]);
			shell->exit_value = 127;
		}
		tmp = tmp->next;
	}
	// Wait for all children
	tmp = shell->cmds;
	while (tmp)
	{	if (tmp->pid > 0)
			waitpid(tmp->pid, NULL, 0);
		tmp = tmp->next;
	}
	// Close pipes
	tmp = shell->cmds;
	close_pipes(tmp);
}