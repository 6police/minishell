#include "redirections.h"

static char	*generate_heredoc_filename(void)
{
	static int	counter;
	char		*num_str;
	char		*filename;

	num_str = ft_itoa(counter++); // static int nao preciso de inicializar ??
	filename = ft_strjoin("/tmp/minishell_heredoc_", num_str);
	free(num_str);
	return (filename);
}

static int	create_heredoc(t_redir *redir)
{
	char	*line;
	char	*filename;
	int		fd;

	filename = generate_heredoc_filename();
	fd = open(filename, O_WRONLY | O_CREAT | O_EXCL, 0600);
	if (fd == -1)
	{
		free(filename);
		return (-1);
	}
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, redir->heredoc->delim) == 0)
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, fd);
		ft_putchar_fd('\n', fd);
		free(line);
	}
	close(fd);
	redir->heredoc->file = filename;
	return (open(filename, O_RDONLY));
}

int	ft_redir_heredoc(t_cmd *cmd, t_shell *shell)
{
	int i;
	int fd;
	t_redir *redir;

	i = -1;
	while (cmd->redirs[++i])
	{
		redir = cmd->redirs[i];
		if (redir->heredoc && redir->heredoc->delim)
		{
			fd = create_heredoc(redir);
			if (fd == -1)
			{
				ft_putstr_fd("minishell: heredoc failed\n", STDERR_FILENO);
				shell->exit_value = EXIT_FAILURE;
				return (-1);
			}
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
	}
	return (0);
}