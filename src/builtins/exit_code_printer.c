// exit status of the last executed function/program/command

#include "ft_builtins.h"

void	exit_code_printer(t_cmd *cmd, t_shell *shell)
{
	if (shell->is_pipe)
	{
		cmd->pid = fork();
	}
	(void)cmd;
	ft_printf_fd(cmd->fd[1], "%d: command not found\n", shell->exit_value);
}