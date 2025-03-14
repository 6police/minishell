#include "ft_builtins.h"

void echo_shell(t_cmd *cmd, t_shell *shell)
{
	int newline;
	int i;
	int	a;

	(void)shell;
	newline = 1;
	i = 1;
	a = 1;
	if (!shell)
		return ;
	while (cmd->args[a])
	{
		// if arg == * (wildcard)
		if (ft_strcmp(cmd->args[a], "*") == 0)
			printf("PLACEHOLDER FOR WILDCARD");
		a++;
	}
	if (cmd->args[1] && ft_strcmp(cmd->args[1], "-n") == 0)
	{
		newline = 0;
		i++;
	}
	while (cmd->args[i])
	{
		ft_putstr_fd(cmd->args[i], STDOUT_FILENO);
		if (cmd->args[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	if (newline)
		ft_putchar_fd('\n', STDOUT_FILENO);
}
