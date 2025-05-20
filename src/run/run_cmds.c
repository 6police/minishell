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
			printf("Waiting for pid: %d\n", tmp->pid);
			waitpid(tmp->pid, &status, 0);
			if (WIFSIGNALED(status))
			{
				printf("Signal received: %d\n", WTERMSIG(status));
				if (WTERMSIG(status) == SIGQUIT)
					ft_printf_fd(STDERR_FILENO, "Quit (core dumped)\n");
				shell->exit_value = 128 + WTERMSIG(status);
				break ;
			}
			else if (WIFEXITED(status))
			{
				printf("Exit status: %d\n", WEXITSTATUS(status));
				shell->exit_value = WEXITSTATUS(status);
				break ;
			}
		}
		printf("alguma coisa\n");
		tmp = tmp->next;
	}
	setup_signals();
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
