#include "ft_builtins.h"

static bool	is_there_quotes(char *str);
static void	do_echo(char *arg, int a);

void	echo_shell(t_cmd *cmd, t_shell *shell)
{
	int	newline;
	int	i;

	(void)shell;
	newline = 1;
	i = -1;
	if (!cmd || !cmd->args)
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		return ;
	}
	if (cmd->args[0] && ft_strcmp(cmd->args[0], "-n") == 0)
		newline = 0;
	while (cmd->args[++i])
	{
		if (check_wildcard(cmd->args[i]))
			do_wildcard(cmd->args[i]);
		else 
			do_echo(cmd->args[i], 0);
		if (cmd->args[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
	}
	if (newline)
		ft_putchar_fd('\n', STDOUT_FILENO);
}
static void	do_echo(char *arg, int a)
{
	if (a == 0)
		ft_putstr_fd(arg, STDOUT_FILENO);
/*	else if (a == 1)
	struc dirent	*entry;
	else if (a == 2)
	
	else if (a == 3)
	
	else if (a == 2)
	//	continue ; //palceholder
	else if (a == 3)
	//	continue ; //palceholder
	else if (a == 4)
	//	continue ; //palceholder*/
	else
		return ;
}
