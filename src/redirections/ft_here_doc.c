#include "redirections.h"

// function to handle heredoc in a child process
void	do_heredoc_child(char *limiter, t_shell *shell)
{
	char	*line;
	int		fd;

	fd = open(HERE_DOC, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	shell->status = fd;
	if (fd < 0)
		exit(1);
	t_pid()->shull = shell;
	while (1)
	{
		line = readline("> ");
		if (!line || (ft_strcmp(line, limiter) == 0))
		{
			free(line);
			break ;
		}
		if (has_expansion(line))
			line = ft_expand(line, shell);
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	close(fd);
	if (shell->is_pipe)
		close_pipes(shell->cmds);
	clean_exit(&shell);
}

// function to handle heredoc in the main shell process
int 	ft_handle_heredoc(t_fd *fd_struct, t_shell *shell)
{
	pid_t	pid;
	static int	status;

	pid = -1;
	shell->hd = true;
	setup_signals(shell);
	shell->exit_value = 0;
	pid = fork();
	if (pid == 0)
	{
		setup_signals_heredoc(shell);
		shell->is_child = true;
		do_heredoc_child(fd_struct->file, shell);
	}
	else
	{
			waitpid(pid, &status, 0);
			if (WIFSIGNALED(status))
			{
				if (WTERMSIG(status) == SIGINT)
					ft_putstr_fd("\n", STDERR_FILENO);
				else if (WTERMSIG(status) == SIGQUIT)
					ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
				shell->exit_value = 128 + WTERMSIG(status);
			}
			else if (WIFEXITED(status))
				shell->exit_value = WEXITSTATUS(status);
	}
	setup_signals(shell);
	return (shell->exit_value);
}
