#include "ft_builtins.h"

void	exit_shell(t_cmd *cmd, t_shell *shell)
{
	(void)cmd;
	printf("COOOOONA \n");
	clean_exit(&shell);
}
