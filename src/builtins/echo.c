#include "ft_builtins.h"

void	echo_shell(t_cmd *cmd, t_shell *shell)
{
	int	newline;
	int	i;
	int	a;

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
	else if (a == 1)
		
	else if (a == 2)
	
	else if (a == 3)
	
	else if (a == 2)
	//	continue ; //palceholder
	else if (a == 3)
	//	continue ; //palceholder
	else if (a == 4)
	//	continue ; //palceholder
	else
		return ;
}


static void	do_wildcard(char *arg)
{
	int	a;
	
	a = 0;
	if (check_for_quotes(arg) == true)
		return ;
	a = check_wildcard_type(arg);
	do_echo(arg, a);
}

static bool	check_for_quotes(char *str)
{
	int		i;

	i = -1;
	while (str[++i])
	{
		if ((str[i] == '\'' || str[i] == '\"'))
			return (true);
	}
	return (false);
}

static int	check_wildcard_type(char *str)
{
	int	wild_card_type;

	wild_card_type = 0;
	// * .* *. *.* '\"'
	if (str[0] == '*' && !str[1]) // *
		wild_card_type = 1;
	else if (str[0] == '*' && str[1] != '\0') // *.
		wild_card_type = 2;
	else if (str[0] != '\0' && str[ft_strlen(str) - 1] == '*') // .*
		wild_card_type = 3;
	else if (str[0] == '*' && str[ft_strlen(str) - 1] == '*') // *.*
		wild_card_type = 4;
	return (wild_card_type);
}