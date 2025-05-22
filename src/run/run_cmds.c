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

// static void close_reds(t_shell *shell){}

void	run_commands(t_shell *shell)
{
	t_cmd	*tmp;
	// int		backup_stdin;
	// int		backup_stdout;

	// backup_stdin = -1;
	// backup_stdout = -1;
	// backup_stdin = dup(STDIN_FILENO);
	// backup_stdout = dup(STDOUT_FILENO);
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
			ft_printf_fd(STDERR_FILENO, "%s command: not found\n",
				tmp->args[0]);
			shell->exit_value = 127;
		}
		tmp = tmp->next;
	}
	if (shell->is_pipe)
		close_pipes(shell->cmds);
	if (shell->wait)
		wait_commands(shell);
	// dup2(backup_stdin, STDIN_FILENO);
	// close(backup_stdin);
	// dup2(backup_stdout, STDOUT_FILENO);
	// close(backup_stdout);
}
