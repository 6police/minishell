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
		// handle_redirections(tmp, shell);
		if (tmp->fd_struct)
		{
			// manage_redirs(tmp->fd_struct, shell);
			// if (assign_redirs(tmp, shell) != 0)
			// {
			// 	shell->exit_value = 1;
			// 	return ;
			// }
			setup_redirections(tmp, shell);
		}
		if (tmp->is_valid)
		{
			pipe_builtin(tmp, shell);
		}
		tmp = tmp->next;
	}
}

void	pipe_builtin(t_cmd *cmd, t_shell *shell)
{
	t_cmd *tmp;

	tmp = cmd;
	if (shell->is_pipe == true && tmp->is_builtin == true)
	{
		tmp->pid = fork();
		if (tmp->pid == 0)
		{
			signal(SIGQUIT, SIG_DFL);
			signal(SIGINT, SIG_DFL);

			shell->is_child = true;
			tmp->builtin_func(tmp, shell);

			if (tmp->fd[1] != STDOUT_FILENO)
				close(tmp->fd[1]);
			if (tmp->fd[0] != STDIN_FILENO)
				close(tmp->fd[0]);

			clean_exit(&shell);
		}
		else if (tmp->pid < 0)
		{
			ft_printf_fd(tmp->fd[1], "minishell: fork failed\n");
			shell->exit_value = 1;
		}
		else
		{
			waitpid(tmp->pid, &shell->exit_value, 0);
			if (WIFSIGNALED(shell->exit_value))
			{
				if (WTERMSIG(status) == SIGQUIT)
					ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
				shell->exit_value = 128 + WTERMSIG(status);
			}
			else if (WIFEXITED(shell->exit_value))
				shell->exit_value = WEXITSTATUS(shell->exit_value);

			if (tmp->fd[1] != STDOUT_FILENO)
				close(tmp->fd[1]);
			if (tmp->fd[0] != STDIN_FILENO)
				close(tmp->fd[0]);
		}
	}
	else
		cmd->builtin_func(tmp, shell);
}