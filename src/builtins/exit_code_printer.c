#include "ft_builtins.h"

// function to print the exit code
void	exit_code_printer(t_cmd *cmd, t_shell *shell)
{
	if (shell->is_pipe)
	{
		cmd->pid = fork();
	}
	(void)cmd;
	ft_printf_fd(STDOUT_FILENO, "%d: command not found\n", shell->exit_value);
}
