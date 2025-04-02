#include "ft_run.h"

void	run_commands(t_shell *shell)
{
	t_cmd *tmp;

	if (!shell->cmds)
		return ;
	tmp = shell->cmds;
	while (tmp)
	{
		if (tmp->is_valid)
			tmp->builtin_func(tmp, shell);
		tmp = tmp->next;
	}
}