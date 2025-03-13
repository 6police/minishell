#include "ft_builtins.h"

void execute_external(t_shell *shell, t_cmd *cmd)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		if (execve(cmd->path, cmd->args, shell->env) == -1)
		{
			ft_putstr_fd("minishell: command not found: ", 2);
			ft_putstr_fd(cmd->name, 2);
			ft_putstr_fd("\n", 2);
			exit(127);
		}
	}
	else if (pid < 0)
		ft_putstr_fd("minishell: fork failed\n", 2);
	else
		waitpid(pid, &status, 0);
}
