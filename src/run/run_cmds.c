#include "ft_run.h"

void wait_commands(t_shell *shell)
{
	t_cmd *tmp;
	int status;

	if (!shell->cmds)
		return ;

	tmp = shell->cmds;
	while (tmp)
	{
		if (tmp->pid > 0)
		{
			waitpid(tmp->pid, &status, 0);
			if (WIFSIGNALED(status))
			{
				if (WTERMSIG(status) == SIGINT)
					ft_putstr_fd("\n", STDERR_FILENO);
				else if (WTERMSIG(status) == SIGQUIT)
					ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
				shell->exit_value = 128 + WTERMSIG(status);
			}
			else if (WIFEXITED(status))
				shell->exit_value = WEXITSTATUS(status);
		}
		tmp = tmp->next;
	}
	setup_signals(shell);
}

void	run_commands(t_shell *shell)
{
	t_cmd *tmp;

	if (!shell->cmds)
		return ;

	tmp = shell->cmds;
	if (shell->is_pipe)
		if (make_pipes(tmp, shell) == 1)
			return ;
	while (tmp)
	{
		if (tmp->is_valid)
			processor(tmp, shell);
		else
		{
			ft_printf_fd(STDERR_FILENO, "%s command: not found\n", tmp->args[0]);
			shell->exit_value = 127;
		}
		tmp = tmp->next;
	}
	if (shell->is_pipe)
		close_pipes(shell->cmds);
	if (shell->wait)
		wait_commands(shell);
}
