#include "redirections.h"

int ft_redir_append(t_cmd *cmd, t_shell *shell)
{
	int		i;
	int		fd;
	t_redir	*redir;

	i = -1;
	while (cmd->redirs[++i])
	{
		redir = cmd->redirs[i];
		if (redir->redir_append)
		{
		fd = open(redir->redir_append, O_WRONLY | O_CREAT | O_APPEND, 0644); //0644 sao permissoees, ver chmod 777, falar com o jony
		if (fd == -1)
		{
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			ft_putstr_fd(redir->redir_append, STDERR_FILENO);
			ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
			shell->exit_value = EXIT_FAILURE;
			return (-1);
		}
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
	}
	return (0);
}