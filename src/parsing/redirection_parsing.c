#include "ft_parsing.h"

int	check_for_redirs(char *token)
{
	int	fwd;
	int	bwd;
	int	dbl_fwd;
	int	hd;
	int	result;

	// check if the token is NULL
	if (token == NULL)
	{
		ft_printf_fd(STDIN_FILENO, "Error: token is NULL\n");
		return (-1);
	}
	fwd = 0;
	bwd = 0;
	dbl_fwd = 0;
	hd = 0;
	fwd = forward_redir_count(token);
	bwd = back_redir_count(token);
	dbl_fwd = dbl_forward_redir_count(token);
	hd = here_doc_count(token);
	// ft_printf_fd(STDIN_FILENO, "Token: %s\n", token);
	// ft_printf_fd(STDIN_FILENO, "Forward redirection count: %d\n", fwd);
	// ft_printf_fd(STDIN_FILENO, "Backward redirection count: %d\n", bwd);
	// ft_printf_fd(STDIN_FILENO, "Double forward redirection count: %d\n",
		// dbl_fwd);
	// ft_printf_fd(STDIN_FILENO, "Here document count: %d\n", hd);
	result = fwd + bwd + dbl_fwd + hd;
	if (result > 0)
		return (result);
	else
		return (0);
}

void	check_redir(char *token, int *j)
{
	int	i;
	int	c;

	c = 0;
	i = *j;
	while (token[i] != '\0')
	{
		if ((token[i] == '"' || token[i] == '\'') && !c)
			c = token[i];
		else if ((token[i] == '>' || token[i] == '<' || token[i] == ' ') && !c)
			break ;
		else if (token[i] == c)
			c = 0;
		i++;
	}
	*j = i;
}

// function to treat tokens and corresponding redirections
// it searches for the next redir
// takes the token and separates it by redirections
char	**split_into_redirs(char *line)
{
	int		total_redirs;
	char	**redirs;
	int		i;
	int		j;
	int		k;

	total_redirs = (check_for_redirs(line));
	if (total_redirs == 0)
		return (NULL);
	redirs = ft_calloc(total_redirs + 1, sizeof(char *));
	if (redirs == NULL)
	{
		ft_printf_fd(STDIN_FILENO, "Error: malloc failed\n");
		return (NULL);
	}
	k = 0;
	i = 0;
	j = 0;
	while (k < total_redirs)
	{
		while (line[i] != '\0' && (line[i] != '>' && line[i] != '<'))
			i++;
		j = i + 1;
		if (line[i] == line[j])
			j++;
		while (line[j] == ' ')
			j++;
		check_redir(line, &j);
		redirs[k] = ft_substr(line, i, j - i);
		if (redirs[k] == NULL)
		{
			ft_printf_fd(STDIN_FILENO, "Error: malloc failed\n");
			free(redirs);
			return (NULL);
		}
		i = j;
		k++;
	}
	redirs[k] = NULL;
	return (redirs);
}
