#include "ft_builtins.h"

void exit_shell(t_shell *shell, t_cmd *cmd)
{
	if (!shell)
		return ;
	clean_exit(shell);
}
