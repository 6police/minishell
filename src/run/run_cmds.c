#include "ft_run.h"

void	run_commands(t_shell *shell)
{
	t_cmd *tmp;

	if (!shell->cmds)
		return ;
	// ft_printf(BLUE "running commands\n" RESET);
	tmp = shell->cmds;
	if (!tmp)
		return ;

	while (tmp)
	{
		if (tmp->is_valid)
		{
			if (shell->is_pipe)
				dup_handles(tmp, shell);
			// close the pipes
			if (tmp->next)
				close(tmp->fd[1]);
			if (tmp->prev)
				close(tmp->prev->fd[0]);
			// execute the command
			tmp->builtin_func(tmp, shell);
			// standardize the exit status
			shell->exit_value = 0;
		}
		else
		{
			if (!shell->is_pipe)
				ft_printf(RED "Command not valid: %s\n" RESET, tmp->name);
			shell->exit_value = 127;
		}
		tmp = tmp->next;
	}
}