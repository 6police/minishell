#include "redirections.h"

static bool	has_expansion(char *line)
{
	int		i;
	int		count_quotes;
	bool	expansion;

	i = 0;
	count_quotes = 0;
	expansion = false;
	while (line[i])
	{
		if ((line[i] == '\'' || line[i] == '"') && !count_quotes)
			count_quotes = line[i];
		else if (count_quotes && line[i] == count_quotes)
			count_quotes = 0;
		else if (line[i] == '$' && !count_quotes)
		{
			expansion = true;
			break ;
		}
		i++;
	}
	return (expansion);
}

static char *ft_expand(char *line, t_shell *shell)
{
	if (!line)
		return (NULL);

	char	*expanded_line;
	t_cmd *tmp;
	char *arg;
	char *aux;
	
	expanded_line = NULL;
	tmp = NULL;
	arg = ft_strdup(line);
	aux = arg;
	if (!arg)
		return (NULL);
	tmp = ft_calloc(sizeof(t_cmd), 1);
	if (!tmp)
	{
		free(arg);
		return (NULL);
	}
	tmp->args = &arg;
	dollar_sign(tmp, shell);
	expanded_line = ft_strdup(tmp->args[0]);
	free(line);
	tmp->args = NULL;
	free(aux);
	free(arg);
	free(tmp);
	return (expanded_line);
}

static void	close_hd(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	exit(130); // Signal exit status for SIGINT
}

void	do_heredoc_child(char *limiter, t_shell *shell)
{
	char	*line;
	int		fd;

	signal(SIGINT, close_hd);      // Catch Ctrl+C
	signal(SIGQUIT, SIG_IGN);      // Ignore 'Ctrl+ \'

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
	clean_exit(&shell); // Clean up and exit
}




void	ft_handle_heredoc(t_fd *fd_struct, t_shell *shell)
{
	pid_t	pid;
	int		status;

	shell->hd = true;
	pid = fork();
	if (pid == 0)
	{
		shell->is_child = true;
		do_heredoc_child(fd_struct->file, shell);
	}
	else
	{
		signal(SIGINT, SIG_IGN); // Ignore Ctrl+C in parent during heredoc
		waitpid(pid, &status, 0);
		if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
			shell->exit_value = 130;
		setup_signals(); // Restore signal handling
	}
}


