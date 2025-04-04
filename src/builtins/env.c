#include "ft_builtins.h"

void env(t_cmd *cmd, t_shell *shell)
{
	(void)cmd;
	print_env(shell->env, cmd);
	shell->exit_value = 0;
}