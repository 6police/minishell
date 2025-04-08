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
			tmp->builtin_func(tmp, shell); // run the command
			shell->exit_value = 0;         // reset exit value
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