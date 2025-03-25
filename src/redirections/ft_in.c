#include "redirections.h"

int	ft_redir_in(t_cmd *cmd, t_shell *shell)
{
	int i;
	int fd;
	t_redir *redir;

	i = -1;
	while (cmd->redirs[++i])
	{
		redir = cmd->redirs[i];
		if (redir->redir_in)
		{
			fd = open(redir->redir_in, O_RDONLY);
			if (fd == -1)
			{
				ft_putstr_fd("minishell: ", STDERR_FILENO);
				ft_putstr_fd(redir->redir_in, STDERR_FILENO);
				ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
				shell->exit_value = EXIT_FAILURE;
				return (-1);
			}
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
	}
	return (0);
}