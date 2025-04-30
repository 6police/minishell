#include "ft_run.h"

static void	pipe_builtin(t_cmd *cmd, t_shell *shell);

void	run_commands(t_shell *shell)
{
	t_cmd	*tmp;

	if (!shell->cmds)
		return ;
	tmp = shell->cmds;
	while (tmp)
	{
		if (tmp->fd_struct)
		{
			manage_redirs(tmp->fd_struct, shell);
			assign_redirs(tmp, shell);
		//	close_cmd_redirs(tmp);
		}
		if (tmp->is_valid)
		{
			//handle_redirections(tmp, shell);
			pipe_builtin(tmp, shell);
		}
		tmp = tmp->next;
	}
}

void	pipe_builtin(t_cmd *cmd, t_shell *shell)
{
	if (shell->is_pipe == true && cmd->is_builtin == true)
	{
		cmd->pid = fork();
		if (cmd->pid == 0)
		{
			signal(SIGQUIT, SIG_DFL);
			signal(SIGINT, SIG_DFL);
			shell->is_child = true;
			cmd->builtin_func(cmd, shell);
			clean_exit(&shell);
		}
		else if (cmd->pid < 0)
		{
			ft_printf_fd(cmd->fd[1], "minishell: fork failed\n");
			shell->exit_value = 1;
		}
		else
		{
			waitpid(cmd->pid, &shell->exit_value, 0);
			if (WIFSIGNALED(shell->exit_value))
			{
				if (WTERMSIG(shell->exit_value) == SIGQUIT)
					ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
				shell->exit_value = 128 + WTERMSIG(shell->exit_value);
			}
			else if (WIFEXITED(shell->exit_value))
				shell->exit_value = WEXITSTATUS(shell->exit_value);
		}
	}
	else
		cmd->builtin_func(cmd, shell);
}