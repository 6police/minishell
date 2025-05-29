#include "ft_builtins.h"

void	env(t_cmd *cmd, t_shell *shell)
{
	cmd->is_builtin = true;
	print_env(shell->env, cmd);
	shell->exit_value = 0;
}
