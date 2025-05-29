#include "redirections.h"

// function to handle Ctrl+C in heredoc
static void	close_hd(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	exit(130); // Signal exit status for SIGINT
}

// function to handle heredoc in a child process
void	do_heredoc_child(char *limiter, t_shell *shell)
{
	char	*line;
	int		fd;

	signal(SIGINT, close_hd);
	signal(SIGQUIT, SIG_IGN);
	fd = open(HERE_DOC, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		exit(1);
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
void	ft_handle_heredoc(t_fd *fd_struct, t_shell *shell)
{
	pid_t	pid;
	int		status;

	pid = -1;
	shell->hd = true;
	pid = fork();
	if (pid == 0)
	{
		shell->is_child = true;
		do_heredoc_child(fd_struct->file, shell);
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		waitpid(pid, &status, 0);
		if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
			shell->exit_value = 130;
		setup_signals();
	}
}
