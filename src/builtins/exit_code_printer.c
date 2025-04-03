// exit status of the last executed function/program/command

# include "ft_builtins.h"

void	exit_code_printer(t_cmd *cmd, t_shell *shell)
{
	// temos de tratar em pipe, penso que mais nenhum command pode correr se houver $?!!
	(void)cmd;
	shell->exit_str_code = "command not found";
	printf("%d: %s\n", shell->exit_value, shell->exit_str_code);
	shell->exit_value = 127;
	//example:
/* 	if (shell->exit_value == 127)
	{
		ft_putstr_fd("127: command not found\n", 2);
	}
	else if (shell->exit_value == 126)
	{
		ft_putstr_fd("126: permission denied\n", 2);
	}
	else if (shell->exit_value == 1)
	{
		ft_putstr_fd("1: syntax error\n", 2);
	} */
}