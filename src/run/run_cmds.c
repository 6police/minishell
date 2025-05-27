#include "ft_run.h"

void	wait_commands(t_shell *shell)
{
	t_cmd	*tmp;

	if (!shell->cmds)
		return ;
	tmp = shell->cmds;
	while (tmp)
	{
		if (tmp->pid > 0)
			waitpid(tmp->pid, &shell->exit_value, 0);
		tmp = tmp->next;
	}
}

void	run_commands(t_shell *shell)
{
	t_cmd	*tmp;

	if (!shell || !shell->cmds)
		return ;
	tmp = shell->cmds;
	if (shell->is_pipe)
		if (make_pipes(tmp, shell) == 1)
			return ;
	while (tmp)
	{
		if (setup_redirections(tmp, shell) == 1)
		{
			shell->exit_value = 1;
			return ;
		}
		if (tmp->is_valid)
			processor(tmp, shell);
		else if (tmp->fd_struct)
			close_fds(tmp);
		else if (!tmp->is_valid && tmp->args && tmp->args[0])
		{
			if (tmp->name)
				ft_printf_fd(STDERR_FILENO, "%s command: not found\n", tmp->args[0]);
			shell->exit_value = 127;
		}
		tmp = tmp->next;
	}
	if (shell->is_pipe)
		close_pipes(shell->cmds);
	if (shell->wait)
		wait_commands(shell);
	close_cmd_redirs(shell->cmds);
}
