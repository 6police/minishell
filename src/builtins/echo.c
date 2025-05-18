#include "ft_builtins.h"

static void	echoing(t_cmd *cmd, bool will_remove_nl);

void	echo_shell(t_cmd *cmd, t_shell *shell)
{
	bool	will_remove_nl;

	will_remove_nl = false;
	(void) shell;
	if (!cmd || !cmd->args)
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		return ;
	}
	if (cmd->args[0] && ft_strcmp(cmd->args[0], "-n") == 0)
		will_remove_nl = true;
	echoing(cmd, will_remove_nl);
	if (will_remove_nl == false)
		ft_putchar_fd('\n', STDOUT_FILENO);
}

static void	echoing(t_cmd *cmd, bool will_remove_nl)
{
	int	i;

	i = -1;
	if (will_remove_nl == true)
		i++;
	while (cmd->args[++i])
	{
		ft_printf_fd(STDOUT_FILENO, "%s", cmd->args[i]);
		// check if there is more so we can put wc_type space ' '
		if (cmd->args[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
	}
}
