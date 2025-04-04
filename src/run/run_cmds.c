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
		{
			handle_redirections(tmp, shell, false);
			tmp->builtin_func(tmp, shell); // nao deviamos trocar por uma funcao chamada execute_command? para que ele veja se e built in ou external?
		}
		tmp = tmp->next;
	}
}