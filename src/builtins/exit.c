#include "ft_builtins.h"

void	exit_shell(t_cmd *cmd, t_shell *shell)
{
	(void)cmd;
	if (!shell->is_child)
		shell->exit_value = 0;
	clean_exit(&shell);
}
