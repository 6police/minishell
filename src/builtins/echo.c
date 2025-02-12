#include "../minishell.h"

/* void echo_shell(t_cmd *cmd)
{
	int newline;
	int i;
	int	a;

	newline = 1;
	i = 1;
	a = 1;

/*	while (cmd->args[a])
	{
		if (cmd->args[a] == "*")
		{
			
		}
		a++;
	}*/
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
} */
