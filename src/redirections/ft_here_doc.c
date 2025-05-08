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



void	ft_handle_heredoc(t_fd *fd_struct, t_shell *shell)
{
	int		fd;
	char	*line;
	char	*limiter;

	limiter = fd_struct->file;
	shell->hd = true;
	fd = open(HERE_DOC, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	while (1)
	{
		line = readline("> ");
		if (!line || (ft_strncmp(line, limiter, ft_strlen(line)) == 0
				&& line[ft_strlen(line)] == '\0'))
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
}
