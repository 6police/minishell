#include "ft_run.h"

void	run_commands(t_shell *shell)
{
	t_cmd *tmp;

	if (!shell->cmds)
		return ;
	// ft_printf(BLUE "running commands\n" RESET);
	tmp = shell->cmds;
	while (tmp)
	{
		if (tmp->is_valid)
		{
			tmp->builtin_func(tmp, shell);
			//standardize the exit status
			shell->exit_status = 0;
		}
		else
		{
			ft_printf(RED "Command not valid: %s\n" RESET, tmp->name);
			shell->exit_status = 127;
		}
		tmp = tmp->next;
	}
}